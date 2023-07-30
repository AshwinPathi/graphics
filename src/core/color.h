// Defines a basic 3 channel color struct (r, g, b)
#pragma once
#include <tuple>
#include <iostream>

namespace graphics {

// A color is just a specially named 3-tuple.
struct Color {
  float r;
  float g;
  float b;
  // No alpha for now

  ///// Helper methods

  // Converts this color into a tuple.
  std::tuple<float, float, float> Tuple() {
    return {r, g, b};
  }

  ///// Operator overloads

  // Scalar multiplication
  constexpr Color operator*(float scalar) const {
    return {r * scalar, g * scalar, b * scalar};
  }

  // Scalar division
  constexpr Color operator/(float scalar) const {
    return *this * 1/scalar;
  }

  // Element wise multiplication with another color.
  constexpr Color operator*(const Color& other) const {
    return {r * other.r, g * other.g, b * other.b};
  }

  // Element wise division with another color.
  constexpr Color operator/(const Color& other) const {
    return {r / other.r, g / other.g, b / other.b};
  }

  // Element wise addition with another color.
  constexpr Color operator+(const Color& other) const {
    return {r + other.r, g + other.g, b + other.b};
  }

  // Element wise subtraction with another color.
  constexpr Color operator-(const Color& other) const {
    return {r - other.r, g - other.g, b - other.b};
  }

  // Self add another color
  Color& operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  // Self subtract another color
  Color& operator-=(const Color& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  // Self scalar multiply
  Color& operator*=(float scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    return *this;
  }

  // Self scalar divide
  Color& operator/=(float scalar) {
    *this *= 1/scalar;
    return *this;
  }

  // Self multiply
  Color& operator*=(const Color& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
  }

  // Self divide
  Color& operator/=(const Color& other) {
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
  }


  // Index into the color like you would with an array.
  float& operator[](const int i) {
    return i == 0 ? r : (i == 1 ? g : b); 
  }
  const float& operator[](const int i) const {
    return i == 0 ? r : (i == 1 ? g : b);
  }
};

/*
std::ostream& operator<<(std::ostream &os, const Color& c) {
  return (os << '(' << c.r << ", " << c.g << ", " << c.b << ')');
}
*/

// Aliases for various colors.
static constexpr Color RED = Color{1.0, 0., 0.};
static constexpr Color GREEN = Color{0.0, 1.0, 0.};
static constexpr Color BLUE = Color{0.0, 0., 1.0};

} // graphics
