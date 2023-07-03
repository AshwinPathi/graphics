/*
Some functions for fast (constexpr) math functions.
*/
#pragma once
#include <cmath>

namespace graphics::math {

// https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <
  typename T,
  typename = typename std::enable_if_t<std::is_floating_point_v<T>, T>
>
constexpr T sqrtHelper(T x, T curr, T prev) {
  return curr == prev
    ? curr
    : sqrtHelper(x, static_cast<T>(0.5) * (curr + x / curr), curr);
}

template <
  typename T,
  typename = typename std::enable_if_t<std::is_floating_point_v<T>, T>
>
constexpr T sqrt(T x) {
  if (std::is_constant_evaluated()) {
    return x >= 0 && x < std::numeric_limits<T>::infinity()
      ? sqrtHelper(x, x, static_cast<T>(0))
      : std::numeric_limits<T>::quiet_NaN();
  } else {
    return std::sqrt(x);
  }
}

} // graphics::math
