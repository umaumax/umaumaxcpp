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

TEST(streampp_test, array) {
  std::stringstream ss;
  std::array<int, 4> ary = {{0, 1, 2, 3}};
  ss << ary;
  EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
}

TEST(streampp_test, raw_array) {
  {
    std::stringstream ss;
    int ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    int8_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    int16_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    int32_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    int64_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    uint8_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    uint16_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    uint32_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    uint64_t ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    float ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
  {
    std::stringstream ss;
    double ary[4] = {0, 1, 2, 3};
    ss << ary;
    EXPECT_EQ(ss.str(), "[4]:{0, 1, 2, 3}");
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
