/* Basic vector classes. Has definitions for:
- Vector<T, Dims> 
- Vector<T, 2>
- Vector<T, 3>
- Vector<T, 4>

And some useful aliases like
- Vector3f
- Color3f
- Color3

Vectors are as constexpr as possible to allow maximal compile time computation.
*/
#pragma once

#include <iostream>

#include "../math/fast_math.h"

namespace graphics::math {

template <typename T, size_t Dims>
struct Vector {
  // Represent a vector with an arbitrary stack allocated array of values.
  T data[Dims];

  // Self multiply by scalar
  constexpr Vector<T, Dims>& operator*=(const T scalar) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  // Self divide by scalar
  constexpr Vector<T, Dims>& operator/=(const T scalar) {
    *this *= 1./scalar;
    return *this;
  }

  // Self add another vector
  constexpr Vector<T, Dims>& operator+=(const Vector<T, Dims>& other) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] += other.data[i];
    }
    return *this;
  }

  // Self subtract another vector
  constexpr Vector<T, Dims>& operator-=(const Vector<T, Dims>& other) noexcept {
    *this += -other;
    return *this;
  }

  // Access element transparently
  T& operator[](const int i) {
    return data[i]; 
  }

  // Access element transparently, const
  constexpr T& operator[](const int i) const {
    return data[i];
  }
};

// Define special partial template specializations for commonly used vector types

// Vector2
template <typename T>
struct Vector<T, 2> {
  static constexpr size_t Dims = 2;
  union {
    T data[Dims];
    struct { T x, y; };
  };

  // Self multiply by scalar
  constexpr Vector<T, Dims>& operator*=(const T scalar) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  // Self divide by scalar
  constexpr Vector<T, Dims>& operator/=(const T scalar) {
    *this *= 1./scalar;
    return *this;
  }


  // Self add another vector
  constexpr Vector<T, Dims>& operator+=(const Vector<T, Dims>& other) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] += other.data[i];
    }
    return *this;
  }

  // Self subtract another vector
  constexpr Vector<T, Dims>& operator-=(const Vector<T, Dims>& other) noexcept {
    *this += -other;
    return *this;
  }

  // Access element transparently
  T& operator[](const int i) {
    return data[i]; 
  }

  // Access element transparently, const
  constexpr T& operator[](const int i) const {
    return data[i];
  }
};

// Vector3, Color3
template <typename T>
struct Vector<T, 3> {
  static constexpr size_t Dims = 3;
  union {
    T data[Dims];
    struct { T x, y, z; };
    struct { T r, g, b; };
  };

  // Self multiply by scalar
  constexpr Vector<T, Dims>& operator*=(const T scalar) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  // Self divide by scalar
  constexpr Vector<T, Dims>& operator/=(const T scalar) {
    *this *= 1./scalar;
    return *this;
  }

  // Self add another vector
  constexpr Vector<T, Dims>& operator+=(const Vector<T, Dims>& other) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] += other.data[i];
    }
    return *this;
  }

  // Self subtract another vector
  constexpr Vector<T, Dims>& operator-=(const Vector<T, Dims>& other) noexcept {
    *this += -other;
    return *this;
  }

  // Access element transparently
  T& operator[](const int i) {
    return data[i]; 
  }

  // Access element transparently, const
  constexpr T& operator[](const int i) const {
    return data[i];
  }
};

// Vector4 (has w dimension), Color4 (has alpha channel)
template <typename T>
struct Vector<T, 4> {
  static constexpr size_t Dims = 4;
  union {
    T data[Dims];
    struct { T x, y, z, w; };
    struct { T r, g, b, a; };
  };

  // Self multiply by scalar
  constexpr Vector<T, Dims>& operator*=(const T scalar) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  // Self divide by scalar
  constexpr Vector<T, Dims>& operator/=(const T scalar) {
    *this *= 1./scalar;
    return *this;
  }

  // Self add another vector
  constexpr Vector<T, Dims>& operator+=(const Vector<T, Dims>& other) noexcept {
    for (int i = 0; i < Dims; i++) {
      data[i] += other.data[i];
    }
    return *this;
  }

  // Self subtract another vector
  constexpr Vector<T, Dims>& operator-=(const Vector<T, Dims>& other) noexcept {
    *this += -other;
    return *this;
  }

  // Access element transparently
  T& operator[](const int i) {
    return data[i]; 
  }

  // Access element transparently, const
  constexpr T& operator[](const int i) const {
    return data[i];
  }
};

// These are free standing functions so we don't have to reimplement them
// for specialized template classes.

// Squared magnitude of a vector
template <typename T, size_t Dims>
constexpr T magnitude_sq(const Vector<T, Dims>& vec) noexcept {
  // Squared magnitude of a vector is the dot product with itself.
  return vec * vec;
}

// Magnitude of a vector
template <typename T, size_t Dims>
constexpr T magnitude(const Vector<T, Dims>& vec) noexcept {
  return math::sqrt(magnitude_sq(vec));
}

// Normalized vector
template <typename T, size_t Dims>
constexpr Vector<T, Dims> normalize(const Vector<T, Dims>& vec) {
  return vec * (static_cast<T>(1.0)/magnitude(vec));
}

// Element wise product between two vectors
template <typename T, size_t Dims>
constexpr Vector<T, Dims> elem_prod(const Vector<T, Dims>& v1, const Vector<T, Dims>& v2) {
  Vector<T, Dims> new_v;
  for (int i = 0; i < Dims; i++) {
    new_v.data[i] = v1.data[i] * v2.data[i];
  }
  return new_v;
}

// Scalar multiplication
template <typename T, size_t Dims>
constexpr Vector<T, Dims> operator*(const Vector<T, Dims>& vec, const T scalar) noexcept {
  Vector<T, Dims> new_v;
  for (int i = 0; i < Dims; i++) {
    new_v.data[i] = vec.data[i] * scalar;
  }
  return new_v;
}

// Scalar multiplication, reversed
template <typename T, size_t Dims>
constexpr Vector<T, Dims> operator*(const T scalar, const Vector<T, Dims>& vec) noexcept {
  return vec * scalar;
}

// Scalar division
template <typename T, size_t Dims>
constexpr Vector<T, Dims> operator/(const Vector<T, Dims>& vec, const T scalar) {
  Vector<T, Dims> new_v = vec * 1./scalar;
  return new_v;
}

// Scalar division, reversed
template <typename T, size_t Dims>
constexpr Vector<T, Dims> operator/(const T scalar, const Vector<T, Dims>& vec) {
  return vec / scalar;
}

// Dot product with another vector (note this overrides the * operator, use elem_prod for element wise product)
template <typename T, size_t Dims>
constexpr T operator*(const Vector<T, Dims>& vec, const Vector<T, Dims>& other) noexcept {
  T dot_prod_result{0};
  for (int i = 0; i < Dims; i++) {
    dot_prod_result += (vec.data[i] * other.data[i]);
  }
  return dot_prod_result;
}

// Element wise addition with another vector
template <typename T, size_t Dims>
constexpr Vector<T, Dims> operator+(const Vector<T, Dims>& vec, const Vector<T, Dims>& other) noexcept {
  Vector<T, Dims> new_v;
  for (int i = 0; i < Dims; i++) {
    new_v.data[i] = vec.data[i] + other.data[i];
  }
  return new_v;
}

// Element wise subtraction with another vector.
template <typename T, size_t Dims>
constexpr Vector<T, Dims> operator-(const Vector<T, Dims>& vec, const Vector<T, Dims>& other) noexcept {
  return vec + -other;
}

// Negate elements, elementwise
template <typename T, size_t Dims>
constexpr Vector<T, Dims> operator-(const Vector<T, Dims>& vec) noexcept {
  Vector<T, Dims> new_v;
  for (int i = 0; i < Dims; i++) {
    new_v.data[i] = -vec.data[i];
  }
  return new_v;
}

// Vector equality
template <typename T, size_t Dims>
constexpr bool operator==(const Vector<T, Dims>& v1, const Vector<T, Dims>& v2) noexcept {
  bool equal = true;
  for (int i = 0; i < Dims; i++) {
    equal = equal && v1[i] == v2[i];
  }
  return equal;
}

// Vector inequality
template <typename T, size_t Dims>
constexpr bool operator!=(const Vector<T, Dims>& v1, const Vector<T, Dims>& v2) noexcept {
  return !(v1 == v2);
}

// Cross product between two generic vectors, but it takes the type of the type of the first
// vector. This is only defined for vectors of dimension 3.
template <typename T>
Vector<T, 3> cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2) noexcept {
  return Vector<T, 3>{v1.y * v2.z - v1.z * v2.y,
                      v1.z * v2.x - v1.x * v2.z,
                      v1.x * v2.y - v1.y * v2.x};
}

// Type aliases for commonly used vector types.
using Vector3f = Vector<float, 3>;

// Alias for point, its just a vector but looks nicer.
using Point3f = Vector<float, 3>;

// useful constructs
static constexpr Vector3f ZeroVector = Vector3f{0.,0.,0.};
static constexpr Vector3f OneVector  = Vector3f{1.,1.,1.};
static constexpr Vector3f UnitX      = Vector3f{1.,0.,0.};
static constexpr Vector3f UnitY      = Vector3f{0.,1.,0.};
static constexpr Vector3f UnitZ      = Vector3f{0.,0.,1.};

// Print operator
std::ostream& operator<<(std::ostream& os, const Vector3f& vec) {
    return os << "(x: " << vec.x << " " << ", y: " << vec.y << ", z: " << vec.z << ")";
}

}; // namespace graphics::math
