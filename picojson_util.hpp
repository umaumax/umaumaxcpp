#pragma once

#include <string>
#include <vector>

#include "picojson.h"

template <class T>
struct PicoJsonUtil {
  static T Decode(picojson::value& value);
  static picojson::value Encode(T& value);
};
template <>
int PicoJsonUtil<int>::Decode(picojson::value& value) {
  return static_cast<int>(value.get<double>());
}
template <>
float PicoJsonUtil<float>::Decode(picojson::value& value) {
  return static_cast<float>(value.get<double>());
}
template <>
double PicoJsonUtil<double>::Decode(picojson::value& value) {
  return value.get<double>();
}
template <>
std::string PicoJsonUtil<std::string>::Decode(picojson::value& value) {
  return value.get<std::string>();
}
template <class T>
T PicoJsonUtil<T>::Decode(picojson::value& value) {
  using E = typename T::value_type;
  std::vector<E> ret;
  for (auto&& pico_elem : value.get<picojson::array>()) {
    ret.emplace_back(PicoJsonUtil<E>::Decode(pico_elem));
  }
  return ret;
}

template <>
picojson::value PicoJsonUtil<int>::Encode(int& value) {
  return picojson::value(static_cast<double>(value));
}
template <>
picojson::value PicoJsonUtil<float>::Encode(float& value) {
  return picojson::value(static_cast<double>(value));
}
template <>
picojson::value PicoJsonUtil<double>::Encode(double& value) {
  return picojson::value(value);
}
template <>
picojson::value PicoJsonUtil<std::string>::Encode(std::string& value) {
  return picojson::value(value);
}
template <class T>
picojson::value PicoJsonUtil<T>::Encode(T& values) {
  using E = typename T::value_type;
  picojson::array pico_array;
  for (auto&& e : values) {
    pico_array.emplace_back(PicoJsonUtil<E>::Encode(e));
  }
  return picojson::value(pico_array);
}
