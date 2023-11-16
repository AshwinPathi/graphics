/* Class to represent a ray, which has an origin point and a direction it points in. */
#pragma once

#include "../math/vec.h"

namespace graphics {

class Ray {
public:
  Ray() = default;

  Ray(const math::Point3f& origin, const math::Vector3f& direction) : origin_{origin}, direction_{direction} {}

  math::Point3f at(float t) const { return origin_ + t * direction_; }

  math::Point3f origin() const { return origin_; }
  math::Vector3f direction() const { return direction_; }

private:
  math::Point3f origin_{};
  math::Vector3f direction_{};
};

}  // namespace graphics
