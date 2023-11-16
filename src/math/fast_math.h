// Some functions for fast (constexpr) math functions.
#pragma once
#include <cmath>
#include <type_traits>

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

// (potentially) Compile time square root using newtons method.
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


template <typename T, typename P>
constexpr T powHelper(T base, P pow) {
  static_assert(std::is_arithmetic_v<T>);
  if (pow == 0) {
    return 1;
  }
  return base * powHelper(base, pow - 1);
}

// (potentially) Compile time power function. Can only do compile time power computation
// if the power is an integral type, otherwise falls back to non-constexpr power.
template <typename T, typename P>
constexpr T pow(T base, P pow) {
  if (std::is_constant_evaluated() && std::is_integral_v<P>) {
    return powHelper(base, pow);
  }
  return std::pow(base, pow);
}

} // graphics::math
