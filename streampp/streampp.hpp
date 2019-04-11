#pragma once

#include <ostream>

#include <vector>
template <typename T>
std::ostream& operator<<(std::ostream& ostr, const std::vector<T>& v) {
  ostr << "[" << v.size() << "]:";
  if (v.empty()) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << v.front();
  for (auto itr = ++v.begin(); itr != v.end(); itr++) ostr << ", " << *itr;
  ostr << "}";
  return ostr;
}

#include <array>
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& ostr, const std::array<T, N>& ary) {
  ostr << "[" << ary.size() << "]:";
  if (ary.empty()) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << ary.front();
  for (auto itr = ary.begin() + 1; itr != ary.end(); itr++)
    ostr << ", " << *itr;
  ostr << "}";
  return ostr;
}

namespace internal {
template <typename T, int N>
std::ostream& cout(std::ostream& ostr, T (&ary)[N]) {
  ostr << "[" << N << "]:";
  if (N == 0) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << ary[0];
  for (auto itr = ary + 1; itr != ary + N; itr++) ostr << ", " << *itr;
  ostr << "}";
  return ostr;
}
template <typename T, int N>
std::ostream& cout(std::ostream& ostr, int8_t (&ary)[N]) {
  ostr << "[" << N << "]:";
  if (N == 0) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << static_cast<int32_t>(ary[0]);
  for (auto itr = ary + 1; itr != ary + N; itr++)
    ostr << ", " << static_cast<int32_t>(*itr);
  ostr << "}";
  return ostr;
}
template <typename T, int N>
std::ostream& cout(std::ostream& ostr, uint8_t (&ary)[N]) {
  ostr << "[" << N << "]:";
  if (N == 0) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << static_cast<uint32_t>(ary[0]);
  for (auto itr = ary + 1; itr != ary + N; itr++)
    ostr << ", " << static_cast<uint32_t>(*itr);
  ostr << "}";
  return ostr;
}
}  // namespace internal

#define STREAMPP_DEF_RAW_ARRAY(type)                            \
  template <int N>                                              \
  std::ostream& operator<<(std::ostream& ostr, type(&ary)[N]) { \
    return internal::cout<type, N>(ostr, ary);                  \
  }
STREAMPP_DEF_RAW_ARRAY(int8_t);
STREAMPP_DEF_RAW_ARRAY(int16_t);
STREAMPP_DEF_RAW_ARRAY(int32_t);
STREAMPP_DEF_RAW_ARRAY(int64_t);
STREAMPP_DEF_RAW_ARRAY(uint8_t);
STREAMPP_DEF_RAW_ARRAY(uint16_t);
STREAMPP_DEF_RAW_ARRAY(uint32_t);
STREAMPP_DEF_RAW_ARRAY(uint64_t);
STREAMPP_DEF_RAW_ARRAY(float);
STREAMPP_DEF_RAW_ARRAY(double);

#include <utility>
template <typename Key, typename T>
std::ostream& operator<<(std::ostream& ostr, const std::pair<Key, T>& m) {
  ostr << "{\"" << m.first << "\": " << m.second << "}";
  return ostr;
}
#include <unordered_map>
template <typename Key, typename T>
std::ostream& operator<<(std::ostream& ostr,
                         const std::unordered_map<Key, T>& m) {
  if (m.empty()) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << *m.begin();
  for (auto itr = ++m.begin(); itr != m.end(); itr++) ostr << ", " << *itr;
  ostr << "}";
  return ostr;
}
#include <map>
template <typename Key, typename T>
std::ostream& operator<<(std::ostream& ostr, const std::map<Key, T>& m) {
  if (m.empty()) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << *m.begin();
  for (auto itr = ++m.begin(); itr != m.end(); itr++) ostr << ", " << *itr;
  ostr << "}";
  return ostr;
}
#include <set>
template <typename T>
std::ostream& operator<<(std::ostream& ostr, const std::set<T>& s) {
  if (s.empty()) {
    ostr << "{ }";
    return ostr;
  }
  ostr << "{" << *(s.begin());
  for (auto itr = ++s.begin(); itr != s.end(); itr++) ostr << ", " << *itr;
  ostr << "}";
  return ostr;
}
