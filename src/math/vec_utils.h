// Utilitiy functions for vector calculations.
#pragma once

#include "../math/vec.h"

namespace {

constexpr double kEpsilon = 0.0001;

} // namespace

namespace graphics::math {

// Gets the reflected vector between an incident vector and the normal of the
// surface that the vector hit.
constexpr Vector3f reflect(const Vector3f& incident, const Vector3f& normal) {
  return incident - normal * 2.f * (incident * normal);
}

// Determines if a N-dimensional, vector-like type is "close enough" to 0.
template <typename T, size_t Dims>
constexpr bool near_zero(const Vector<T, Dims>& vec) {
  bool is_near_zero = true;
  for (int d = 0; d < Dims; d++) {
    is_near_zero &= (std::abs(0 - vec.data[d]) < kEpsilon);
  }
  return is_near_zero;
}

} // namespace graphics::math
