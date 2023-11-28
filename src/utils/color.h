#pragma once
#include "../math/math_utils.h"

namespace graphics {

// Color for color types between 0.0 - 1.0.
using Color3f = math::Vector<float, 3>;

// Color for color types between 0 and 255. This is primarily used for PPM outputing.
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

constexpr Color3 clamp_color3(const Color3& color3) {
  return Color3 {
    math::clamp(color3.data[0], 255, 255),
    math::clamp(color3.data[1], 255, 255),
    math::clamp(color3.data[2], 255, 255),
  };
}

constexpr Color3f clamp_color3f(const Color3f& color3) {
  return Color3f {
    math::clamp(color3.data[0], 0.f, 1.f),
    math::clamp(color3.data[1], 0.f, 1.f),
    math::clamp(color3.data[2], 0.f, 1.f),
  };
}

// Some helper aliases for colors.
namespace colors {

static constexpr Color3f Black  = Color3f{0.f ,0.f, 0.f};
static constexpr Color3f White  = Color3f{1.f ,1.f, 1.f};
static constexpr Color3f Red    = Color3f{1.f ,0.f, 0.f};
static constexpr Color3f Green  = Color3f{0.f ,1.f, 0.f};
static constexpr Color3f Blue   = Color3f{0.f ,0.f, 1.f};

} // namespace colors

} // namespace graphics
