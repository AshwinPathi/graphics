#pragma once
#include "../math/math.h"

namespace graphics {

// Color for color types between 0.0 - 1.0.
using Color3f = math::Vector<float, 3>;

// Color for color types between 0 and 255.
using Color3 = math::Vector<int, 3>;

// Useful color helper methods.
// Note have to use data[X] to allow this to be constexpr, since we have to refer to the
// union values by their first element, in this case its |data|.
// see: https://stackoverflow.com/questions/36393588/constexpr-reference-to-a-variable-of-an-anonymous-struct
constexpr Color3 to_color3(const Color3f& color3f) {
  return Color3{
    static_cast<int>(color3f.data[0] * 255.f),
    static_cast<int>(color3f.data[1] * 255.f),
    static_cast<int>(color3f.data[2] * 255.f)
  };
}

// Useful color helper methods
// Note have to use data[X] to allow this to be constexpr.
constexpr Color3f to_color3f(const Color3& color3) {
  return Color3f{color3.data[0] / 255.f, color3.data[1] / 255.f, color3.data[2] / 255.f};
}

} // namespace graphics
