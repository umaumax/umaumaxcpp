#include <sstream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "picojson_util/picojson_util.hpp"

TEST(PicoJsonUtilTest, encode) {
  picojson::object obj;
  std::vector<std::vector<std::vector<float>>> values(3);
  for (auto&& value : values) {
    value = std::vector<std::vector<float>>(3);
    for (auto&& value2 : value) {
      value2 = std::vector<float>(3);
    }
  }
  picojson::value value = PicoJsonUtil<decltype(values)>::Encode(values);
  obj.emplace(std::make_pair("key", value));

  picojson::value v(obj);
  std::stringstream ss;
  v.serialize(std::ostream_iterator<char>(ss));
  EXPECT_EQ(ss.str(),
            "{\"key\":[[[0,0,0],[0,0,0],[0,0,0]],[[0,0,0],[0,0,0],[0,0,0]],[["
            "0,0,0],[0,0,0],[0,0,0]]]}");
}

TEST(PicoJsonUtilTest, decode) {
  picojson::value val;
  std::string err = picojson::parse(val,
                                    "{\"key\":[[[0,0,0],[0,0,0],[0,0,"
                                    "0]],[[0,0,0],[0,0,0],[0,0,0]],[["
                                    "0,0,0],[0,0,0],[0,0,0]]]}");
  if (!err.empty()) {
    FAIL() << err;
  }
  picojson::object& obj = val.get<picojson::object>();
  auto values =
      PicoJsonUtil<std::vector<std::vector<std::vector<float>>>>::Decode(
          obj["key"]);
  std::stringstream ss;
  PicoJsonUtil<decltype(values)>::Encode(values).serialize(
      std::ostream_iterator<char>(ss));
  EXPECT_EQ(ss.str(),
            "[[[0,0,0],[0,0,0],[0,0,0]],[[0,0,0],[0,0,0],[0,0,0]],[[0,0,0],["
            "0,0,0],[0,0,0]]]");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
