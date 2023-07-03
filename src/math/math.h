/*
Helper math functions.
*/
#pragma once
#include "vector.h"

namespace graphics::math {

// Gets the reflected vector between an incident vector and the normal of the
// surface that the vector hit.
template <
  typename T,
  typename = typename std::enable_if_t<std::is_floating_point_v<T>, T>
>
Vector3Impl<T> reflect(const Vector3Impl<T>& incident, const Vector3Impl<T>& normal) {
  return incident - normal * static_cast<T>(2) * (incident * normal);
}

// Linearly interpolates the y value at x using the line created by
// (x1, y1) and (x2, y2).
template <
  typename T,
  typename = typename std::enable_if_t<std::is_floating_point_v<T>, T>
>
constexpr T lerp(T x, T x1, T y1, T x2, T y2) {
  return (y1 * (x2 - x) + y2 * (x - x1)) / (x2 - x1);
}

} // graphics::math
