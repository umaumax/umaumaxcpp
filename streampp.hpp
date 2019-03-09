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

#include <utility>
template <typename Key, typename T>
std::ostream& operator<<(std::ostream& ostr, const std::pair<Key, T>& m) {
  ostr << "{\"" << m.first << "\": "
       << m.second << "}";
  return ostr;
}
#include <unordered_map>
template <typename Key, typename T>
std::ostream& operator<<(std::ostream& ostr, const std::unordered_map<Key, T>& m) {
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
