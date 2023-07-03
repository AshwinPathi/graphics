/*
Represents a basic sphere.
*/
#pragma once

#include "intersectable.h"
#include "../../math/vector.h"
#include "../../math/fast_math.h"
#include "shape_utils.h"

namespace graphics::raytracer {

class Sphere : public IntersectableImpl {

public:
  Sphere() = default;

  Sphere(math::Vector3 center_in, float radius_in, Material material_in) : center{center_in}, radius{radius_in}, IntersectableImpl{material_in} {} 

  ObjectIntersectionInfo objectIntersect(const math::Vector3& origin, const math::Vector3& direction) const override {
    // Check to see if the intersection is inside the sphere or not.
    const bool inside = (center - origin).magnitudesq() < radius * radius;

    const float tc = ((center - origin) * direction) / direction.magnitude();

    // This means we had no intersection with the sphere.
    if (!inside && tc < 0) {
      return kFailedHit;
    }

    // Once again, no intersection with the sphere.
    const float dd = (origin + direction * tc - center).magnitudesq();
		if (!inside and dd > radius * radius) {
      return kFailedHit;
    }

    const float t_offset = math::sqrt(radius * radius - dd) / direction.magnitude();
    float t = tc + (inside ? t_offset : -t_offset);
    return ObjectIntersectionInfo{.hit = true,
                                  .distance = t,
                                  .normal = ((origin + direction * t) - center).normalize()};
  }

public:
  // You can uniquely define a sphere with the center and its radius (and the material properties)
  // inhereted from an intersectable object.
  math::Vector3 center;
  float radius;
};

} // graphics::raytracer
