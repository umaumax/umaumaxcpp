#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "streampp/streampp.hpp"

TEST(streampp_test, vector) {
  std::stringstream ss;
  std::vector<int> vec{0, 1, 2, 3};
  ss << vec;
  EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
}

TEST(streampp_test, map) {
  std::stringstream ss;
  std::map<std::string, int> m{
      {"one", 1},
      {"two", 2},
  };
  ss << m;
  EXPECT_EQ(ss.str(), "{{\"one\": 1}, {\"two\": 2}}");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
