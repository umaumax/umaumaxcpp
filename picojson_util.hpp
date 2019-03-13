#pragma once

#include <string>
#include <vector>

#include "picojson.h"

template <class T>
struct PicoJsonUtil {
  static inline T Decode(picojson::value& value);
  static inline picojson::value Encode(T& value);
};
template <>
inline int PicoJsonUtil<int>::Decode(picojson::value& value) {
  return static_cast<int>(value.get<double>());
}
template <>
inline float PicoJsonUtil<float>::Decode(picojson::value& value) {
  return static_cast<float>(value.get<double>());
}
template <>
inline double PicoJsonUtil<double>::Decode(picojson::value& value) {
  return value.get<double>();
}
template <>
inline std::string PicoJsonUtil<std::string>::Decode(picojson::value& value) {
  return value.get<std::string>();
}
template <class T>
inline T PicoJsonUtil<T>::Decode(picojson::value& value) {
  using E = typename T::value_type;
  std::vector<E> ret;
  for (auto&& pico_elem : value.get<picojson::array>()) {
    ret.emplace_back(PicoJsonUtil<E>::Decode(pico_elem));
  }
  return ret;
}

template <>
inline picojson::value PicoJsonUtil<int>::Encode(int& value) {
  return picojson::value(static_cast<double>(value));
}
template <>
inline picojson::value PicoJsonUtil<float>::Encode(float& value) {
  return picojson::value(static_cast<double>(value));
}
template <>
inline picojson::value PicoJsonUtil<double>::Encode(double& value) {
  return picojson::value(value);
}
template <>
inline picojson::value PicoJsonUtil<std::string>::Encode(std::string& value) {
  return picojson::value(value);
}
template <class T>
inline picojson::value PicoJsonUtil<T>::Encode(T& values) {
  using E = typename T::value_type;
  picojson::array pico_array;
  for (auto&& e : values) {
    pico_array.emplace_back(PicoJsonUtil<E>::Encode(e));
  }
  return picojson::value(pico_array);
}
