// Defines the implementation of various lighting components.
#pragma once

#include "../../math/vec.h"
#include "../../utils/color.h"

namespace graphics::raytracer {

class Light {
public:
  virtual ~Light() = default;

  virtual math::Vector3f Direction(const math::Point3f& illuminated_point) const = 0;

  virtual float Intensity(const math::Point3f& illuminated_point) const = 0;

  virtual Color3f Color() const = 0;

};

} // namespace graphics::raytracer
