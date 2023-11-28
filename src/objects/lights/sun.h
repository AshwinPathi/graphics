// Defines a sun type light source, which is a light source that is infinitely far away
// and emits a light with the highest intensity, with no falloff.
#pragma once

#include "../../objects/lights/light.h"

#include "../../math/vec.h"
#include "../../utils/color.h"

namespace graphics::raytracer {

class Sun : public Light {
public:
  Sun(const math::Point3f position, const Color3f& color) : position_{position}, color_{color} {}

  math::Vector3f Direction([[maybe_unused]] const math::Point3f& illuminated_point) const override {
    // Treat the position of the light as the vector pointing in the direction of the light.
    return position_;
  }

  float Intensity(const math::Point3f& illuminated_point) const override {
    return 1.f;
  }

  Color3f Color() const override {
    return color_;
  }

private:
  math::Point3f position_{};
  Color3f color_{};
};

} // namespace graphics::raytracer
