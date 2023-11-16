// Helper math functions.
#pragma once
#include <type_traits>
#include <algorithm>

#include "../math/vec.h"

namespace graphics::math {

// Gets the reflected vector between an incident vector and the normal of the
// surface that the vector hit.
constexpr Vector3f reflect(const Vector3f& incident, const Vector3f& normal) {
  return incident - normal * 2.f * (incident * normal);
}

// Linearly interpolates the y value at x using the line created by
// (x1, y1) and (x2, y2).
template <typename T>
constexpr T lerp(T x, T x1, T y1, T x2, T y2) {
  return (y1 * (x2 - x) + y2 * (x - x1)) / (x2 - x1);
}

// Clamps a value between a lower and upper bound.
template <typename T>
constexpr T clamp(T value, T lower, T upper) {
  return std::min(std::max(value, lower), upper);
}

} // graphics::math
