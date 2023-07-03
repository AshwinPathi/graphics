/*
Very simple color class. Just represents 3 numeric values for r, g, b.
*/
#pragma once

namespace graphics {

template <
  typename T,
  typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
struct ColorImpl {
  T r;
  T g;
  T b;

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  constexpr ColorImpl<T> operator*(const U scalar) const {
    return ColorImpl<T>{static_cast<T>(r * scalar),
                static_cast<T>(g * scalar),
                static_cast<T>(b * scalar)};
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  constexpr ColorImpl<T> operator*(const ColorImpl<U>& other) const {
    return ColorImpl{static_cast<T>(r * other.r), static_cast<T>(g * other.g), static_cast<T>(b * other.b)};
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  constexpr ColorImpl<T> operator+(const ColorImpl<U>& other) const {
    return ColorImpl{static_cast<T>(r + other.r), static_cast<T>(g + other.g), static_cast<T>(b + other.b)};
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  ColorImpl<T>& operator+=(const ColorImpl<U>& other) {
    r += static_cast<T>(other.r);
    g += static_cast<T>(other.g);
    b += static_cast<T>(other.b);
    return *this;
  }

};

// Color in the range [0.0 - 1.0]. This is used for most ray calculations.
using Color = ColorImpl<float>;


} // graphics
