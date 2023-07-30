#pragma once
#include <iostream>
#include <type_traits>
#include <tuple>

#include "fast_math.h"

namespace graphics::math {

// Vector class to represent 3d point.
template <
  typename T,
  typename = typename std::enable_if_t<std::is_arithmetic_v<T>, T>
>
struct Vector3Impl {
  T x;
  T y;
  T z;

  ///// Helper methods

  // Converts this color into a tuple.
  std::tuple<T, T, T> Tuple() {
    return {x, y, z};
  }

  ///// Mathematical operations
  constexpr T magnitudesq() const {
    return x * x + y * y + z * z;
  }

  constexpr T magnitude() const {
    return math::sqrt(magnitudesq());
  }

  constexpr Vector3Impl<T> normalize() const {
    return *this * (static_cast<T>(1.0)/magnitude());
  }

  ///// Operator overloads
  // Scalar multiply
  constexpr Vector3Impl<T> operator*(const T scalar) const {
    return Vector3Impl<T>{x * scalar, y * scalar, z * scalar};
  }

  // Dot product with another vector
  constexpr T operator*(const Vector3Impl<T>& other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  // Element wise addition with another vector
  constexpr Vector3Impl<T> operator+(const Vector3Impl<T>& other) const {
    return Vector3Impl<T>{x + other.x, y + other.y, z + other.z};
  }

  // Element wise subtraction with another vector.
  constexpr Vector3Impl<T> operator-(const Vector3Impl<T>& other) const {
    return Vector3Impl<T>{x - other.x, y - other.y, z - other.z};
  }

  // Negate vector
  constexpr Vector3Impl<T> operator-() const {
    return Vector3Impl<T>{-x, -y, -z};
  }

  // Self multiply by scalar
  Vector3Impl<T>& operator*=(const T scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  // Self add another vector
  Vector3Impl<T>& operator+=(const Vector3Impl<T>& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  // Self subtract another vector
  Vector3Impl<T>& operator-=(const Vector3Impl<T>& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }


  // Index into the vector3 like you would with an array.
  T& operator[](const int i) {
    return i == 0 ? x : (i == 1 ? y : z); 
  }
  const T& operator[](const int i) const {
    return i == 0 ? x : (i == 1 ? y : z);
  }
};


// Cross product between two generic vectors, but it takes the type of the type of the first
// vector
template <
  typename T,
  typename = typename std::enable_if_t<std::is_arithmetic_v<T>, T>
>
Vector3Impl<T> cross(const Vector3Impl<T>& v1, const Vector3Impl<T>& v2) {
  return Vector3Impl<T>{v1.y * v2.z - v1.z * v2.y,
                        v1.z * v2.x - v1.x * v2.z,
                        v1.x * v2.y - v1.y * v2.x};
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
