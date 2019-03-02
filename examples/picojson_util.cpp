#include <iostream>

#include "umaumaxcpp/picojson_util.hpp"

int main(int argc, char* argv[]) {
  // NOTE: encode
  picojson::object obj;
  {
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
    v.serialize(std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;
  }

  // NOTE: decode
  {
    auto values =
        PicoJsonUtil<std::vector<std::vector<std::vector<float>>>>::Decode(
            obj["key"]);
    // NOTE: for output
    {
      PicoJsonUtil<decltype(values)>::Encode(values).serialize(
          std::ostream_iterator<char>(std::cout));
      std::cout << std::endl;
    }
  }
  return 0;
}
