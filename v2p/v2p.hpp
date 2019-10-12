// This is the virtual memory address to physical memory address library.
#pragma once

#include <unistd.h>  // sysconf

#include <cassert>  // assert
#include <cstring>  // strerror
#include <iostream>
#include <string>
#include <vector>

namespace v2p {
inline uintptr_t VirtToPhys(pid_t pid, uintptr_t vaddr);

class PTE {
 public:
  PTE();
  ~PTE();

  // NOTE: page mapping file Open
  bool Open();
  // NOTE: page mapping file Reopen
  bool Reopen();
  uintptr_t VirtToPhys(uintptr_t vaddr);

  template <typename T>
  inline std::vector<uintptr_t> VirtToPhysRange(uintptr_t vaddr1,
                                                uintptr_t vaddr2,
                                                int stride = 1) {
    return VirtToPhysRange_(vaddr1, sizeof(T), (vaddr2 - vaddr1) / sizeof(T),
                            stride);
  }
  template <typename T>
  inline std::vector<uintptr_t> VirtToPhysSize(uintptr_t vaddr1, size_t size,
                                               int stride = 1) {
    return VirtToPhysRange_(vaddr1, sizeof(T), size, stride);
  }
  // NOTE: page mapping file Close
  bool Close();

 private:
  bool Open_(bool reopen_flag);
  std::vector<uintptr_t> VirtToPhysRange_(uintptr_t vaddr1, int typesize,
                                          size_t size, int stride);

  pid_t pid_;
  FILE *_file;
  size_t pagesize_;
};

inline PTE::PTE()
    : pid_(getpid()), _file(nullptr), pagesize_(sysconf(_SC_PAGESIZE)) {}
inline PTE::~PTE() { Close(); }
inline bool PTE::Open() { return Open_(false); }
inline bool PTE::Reopen() { return Open_(true); }
inline bool PTE::Open_(bool reopen_flag) {
  if (_file != nullptr) {
    if (!reopen_flag) {
      std::cerr << "PTE already Open" << std::endl;
      return false;
    }
    Close();
  }

  std::string pagemap_path = "/proc/" + std::to_string(pid_) + "/pagemap";
  if ((_file = fopen(pagemap_path.c_str(), "r")) != nullptr) {
    return true;
  }
  std::cerr << "PTE Open error : " << strerror(errno) << std::endl;
  return false;
}
inline bool PTE::Close() {
  if (_file != nullptr) {
    int ret = fclose(_file);
    if (ret == 0) return true;
    std::cerr << "PTE Close error : " << strerror(errno) << std::endl;
    return false;
  }
  return true;
}

inline uintptr_t PTE::VirtToPhys(uintptr_t vaddr) {
  assert((_file != nullptr) &&
         ("you must call VirtToPhys after call Open method"));

  uintptr_t paddr = 0;
  size_t offset   = (vaddr / pagesize_) * sizeof(uint64_t);
  if (fseek(_file, offset, SEEK_SET) != 0) {
    std::cerr << "PTE seek error : " << strerror(errno) << std::endl;
    return -1;
  }
  uint64_t e = 0;
  if (!fread(&e, sizeof(uint64_t), 1, _file)) {
    std::cerr << "PTE fread error : " << strerror(errno) << std::endl;
    return -1;
  }
  if ((e & (1ULL << 63)) == 0) {  // page present ?
    std::cerr << "PTE present error : e = " << e << " : maybe not first touch!"
              << std::endl;
    return -1;
  }
  paddr = e & ((1ULL << 54) - 1);  // pfn mask
                                   //	cerr << "paddr pre:" << paddr << endl;
  paddr *= pagesize_;
  // add offset within page
  paddr |= (vaddr & (pagesize_ - 1));
  return paddr;
}

inline std::vector<uintptr_t> PTE::VirtToPhysRange_(uintptr_t vaddr1,
                                                    int typesize, size_t size,
                                                    int stride) {
  assert((size >= 0) || !(std::cerr << "size = " << size << std::endl));
  assert((stride >= 1) || !(std::cerr << "stride = " << stride << std::endl));

  std::vector<uintptr_t> vec(size);
  for (int i = 0; i < size; i += stride) {
    uintptr_t vaddr = vaddr1 + i * typesize;
    uintptr_t paddr = VirtToPhys(vaddr);
    vec[i]          = paddr;
  }
  return vec;
}

// NOTE virtual memory address to physical memory address
// NOTE Please note that updating requires file Reopen
inline uintptr_t VirtToPhys(pid_t pid, uintptr_t vaddr) {
  FILE *pagemap   = nullptr;
  intptr_t paddr  = 0;
  uint64_t e      = 0;
  size_t pagesize = sysconf(_SC_PAGESIZE);
  size_t offset   = (vaddr / pagesize) * sizeof(uint64_t);

  // FYI https://www.kernel.org/doc/Documentation/vm/pagemap.txt
  std::string pagemap_path = "/proc/" + std::to_string(pid) + "/pagemap";
  if ((pagemap != nullptr) || (pagemap = fopen(pagemap_path.c_str(), "r"))) {
    if (lseek(fileno(pagemap), offset, SEEK_SET) == offset) {
      if (fread(&e, sizeof(uint64_t), 1, pagemap)) {
        if (e & (1ULL << 63)) {            // page present ?
          paddr = e & ((1ULL << 54) - 1);  // pfn mask
          paddr = paddr * pagesize;
          // add offset within page
          paddr = paddr | (vaddr & (pagesize - 1));
        }
      } else {
        std::cerr << "error read pagemap : " << std::strerror(errno)
                  << std::endl;
      }
    }
    if (pagemap != nullptr) fclose(pagemap);
  }
  return paddr;
}
}  // namespace v2p
