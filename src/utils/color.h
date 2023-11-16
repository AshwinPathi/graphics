#pragma once
#include "../math/math.h"

namespace graphics {

// Color for color types between 0.0 - 1.0.
using Color3f = math::Vector<float, 3>;

// Color for color types between 0 and 255.
using Color3 = math::Vector<int, 3>;

// Useful color helper methods
inline Color3 to_color3(const Color3f& color3f) {
  return Color3{
    static_cast<int>(color3f.r * 255.f),
    static_cast<int>(color3f.g * 255.f),
    static_cast<int>(color3f.b * 255.f)
  };
}

// Useful color helper methods
inline Color3f to_color3f(const Color3& color3) {
  return Color3f{color3.r / 255.f, color3.g / 255.f, color3.b / 255.f};
}

} // namespace graphics
