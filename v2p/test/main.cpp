#include <map>
#include <memory>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "v2p/v2p.hpp"

class PTEHelper : public v2p::PTE {
 public:
};

class PTETest : public ::testing::Test {
 public:
  virtual void SetUp() { pte_ptr = std::unique_ptr<PTEHelper>(new PTEHelper); }
  virtual void TearDown() {}

  std::unique_ptr<PTEHelper> pte_ptr = nullptr;
};

TEST_F(PTETest, normal) {
  constexpr int PAGE_SIZE = 4096;
  int x                   = 0;
  uintptr_t virt_addr     = reinterpret_cast<uintptr_t>(&x);

  bool Open_ret = pte_ptr->Open();
  EXPECT_TRUE(Open_ret);
  uintptr_t phys_addr = pte_ptr->VirtToPhys(virt_addr);
  EXPECT_EQ(virt_addr % PAGE_SIZE, phys_addr % PAGE_SIZE);
  bool Close_ret = pte_ptr->Close();
  EXPECT_TRUE(Close_ret);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
