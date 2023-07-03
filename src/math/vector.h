#pragma once
#include <iostream>

#include "fast_math.h"

namespace graphics::math {

// Vector class to represent 3d point.
// For all the methods in the vector class, allow them to be performed between multiple
// vectors of different types, but ultimately make sure that the final type of the result
// is the overall type of the vector.
template <
  typename T,
  typename = typename std::enable_if_t<std::is_floating_point_v<T>, T>
>
struct Vector3Impl {
  T x;
  T y;
  T z;

  // Index into the vector3 like you would with an array.
  T& operator[](const int i) {
    return i == 0 ? x : (i == 1 ? y : z); 
  }
  const T& operator[](const int i) const {
    return i == 0 ? x : (i == 1 ? y : z);
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  constexpr Vector3Impl<T> operator*(const U scalar) const {
    return Vector3Impl<T>{static_cast<T>(x * scalar),
                static_cast<T>(y * scalar),
                static_cast<T>(z * scalar)};
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  Vector3Impl<T>& operator*=(const U scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  constexpr T operator*(const Vector3Impl<U>& other) const {
    return static_cast<T>(x * other.x) + static_cast<T>(y * other.y) + static_cast<T>(z * other.z);
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  constexpr Vector3Impl<T> operator+(const Vector3Impl<U>& other) const {
    return Vector3Impl<T>{static_cast<T>(x + other.x),
                static_cast<T>(y + other.y),
                static_cast<T>(z + other.z)};
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  Vector3Impl<T>& operator+=(const U scalar) {
    x += static_cast<T>(scalar);
    y += static_cast<T>(scalar);
    z += static_cast<T>(scalar);
    return *this;
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  constexpr Vector3Impl<T> operator-(const Vector3Impl<U>& other) const {
    return Vector3Impl<T>{static_cast<T>(x - other.x),
                static_cast<T>(y - other.y),
                static_cast<T>(z - other.z)};
  }

  template <
    typename U,
    typename = typename std::enable_if_t<std::is_floating_point_v<U>, U>
  >
  Vector3Impl<T>& operator-=(const U scalar) {
    x -= static_cast<T>(scalar);
    y -= static_cast<T>(scalar);
    z -= static_cast<T>(scalar);
    return *this;
  }

  constexpr Vector3Impl<T> operator-() const {
    return Vector3Impl<T>{static_cast<T>(-x),
                static_cast<T>(-y),
                static_cast<T>(-z)};
  }

  constexpr T magnitudesq() const {
    return x * x + y * y + z * z;
  }

  constexpr T magnitude() const {
    return math::sqrt(magnitudesq());
  }

  constexpr Vector3Impl<T> normalize() const {
    return (*this) * (static_cast<T>(1.0)/magnitude());
  }
};

// Cross product between two generic vectors, but it takes the type of the type of the first
// vector
template <
  typename T,
  typename U,
  typename = typename std::enable_if_t<
    std::is_arithmetic_v<T> && std::is_arithmetic_v<U>,
  T>
>
Vector3Impl<T> cross(const Vector3Impl<T>& v1, const Vector3Impl<U>& v2) {
  return Vector3Impl<T>{static_cast<T>(v1.y*v2.z) - static_cast<T>(v1.z*v2.y),
              static_cast<T>(v1.z*v2.x) - static_cast<T>(v1.x*v2.z),
              static_cast<T>(v1.x*v2.y) - static_cast<T>(v1.y*v2.x)};
}

template <
  typename T,
  typename = typename std::enable_if_t<std::is_arithmetic_v<T>, T>
>
std::ostream& operator << (std::ostream &os, const Vector3Impl<T>& v) {
  return (os << '(' << v.x << ", " << v.y << ", " << v.z << ')');
}

// Alias the usual vector to a float vector.
using Vector3 = Vector3Impl<float>;

// Aliases for useful constructs.
static constexpr Vector3 ZeroVector = Vector3{0.,0.,0.};
static constexpr Vector3 OneVector = Vector3{1.,1.,1.};
static constexpr Vector3 UnitX = Vector3{1.,0.,0.};
static constexpr Vector3 UnitY = Vector3{0.,1.,0.};
static constexpr Vector3 UnitZ = Vector3{0.,0.,1.};

} // graphics::math
