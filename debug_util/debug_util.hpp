#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>

class VarDB {
 public:
  VarDB() {}

  void Append(std::string key, std::string val) { db_[key][val]++; }
  void Clear() { db_.clear(); }
  std::string ToString() {
    std::stringstream ss;
    for (auto& v : db_) {
      std::string key    = v.first;
      auto&& var_val_map = v.second;
      for (auto& v : var_val_map) {
        std::string val = v.first;
        uint64_t cnt    = v.second;
        ss << key << "[" << val << "]=" << cnt << std::endl;
      }
    }
    return ss.str();
  }
  void Print() { std::cout << ToString() << std::endl; }

 protected:
  std::map<std::string, std::map<std::string, uint64_t>> db_;
};
