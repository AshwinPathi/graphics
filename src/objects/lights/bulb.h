// Defines a bulb type light source, which is a light source eminating from a speciifc
// point and falling off with inverse square intensity.
#pragma once

#include "../../objects/lights/light.h"

#include "../../math/vec.h"
#include "../../utils/color.h"

namespace graphics::raytracer {

class Bulb : public Light {
public:
  Bulb(const math::Point3f position, const Color3f& color) : position_{position}, color_{color} {}

  math::Vector3f Direction(const math::Point3f& illuminated_point) const override {
    return position_ - illuminated_point;
  }

  float Intensity(const math::Point3f& illuminated_point) const override {
    // Intensity falls off by inverse square.
    return 1.f / math::magnitude_sq(Direction(illuminated_point));
  }

  Color3f Color() const override {
    return color_;
  }

private:
  math::Point3f position_{};
  Color3f color_{};
};

} // namespace graphics::raytracer
