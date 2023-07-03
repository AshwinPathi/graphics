/*
Represents a basic sphere.
*/
#pragma once

#include "shape.h"
#include "../../math/vector.h"
#include "../utils.h"
#include "../../math/fast_math.h"

namespace graphics {

struct Sphere : ShapeImpl {
  math::Vector3 center;
  float radius;
  Material material;

  Sphere() = default;

  Sphere(math::Vector3 center_in, float radius_in, Material material_in) : center{center_in}, radius{radius_in}, material{material_in} {} 

  ObjectIntersectionInfo objectIntersect(const math::Vector3& origin, const math::Vector3& direction) const override {
    // Check to see if the intersection is inside the sphere or not.
    const bool inside = (center - origin).magnitudesq() < radius * radius;

    const float tc = ((center - origin) * direction) / direction.magnitude();

    // This means we had no intersection with the sphere.
    if (!inside && tc < 0) {
      return ObjectIntersectionInfo{.hit = false, .distance = 0, .normal = math::ZeroVector};
    }

    // Once again, no intersection with the sphere.
    const float dd = (origin + direction * tc - center).magnitudesq();
		if (!inside and dd > radius * radius) {
      return ObjectIntersectionInfo{.hit = false, .distance = 0, .normal = math::ZeroVector};
    }

    const float t_offset = math::sqrt(radius * radius - dd) / direction.magnitude();
    float t;
    if (inside) {
      t = tc + t_offset;
    } else {
      t = tc - t_offset;
    }
    return ObjectIntersectionInfo{.hit = true, .distance = t, .normal = ((origin + direction * t) - center).normalize()};
  }
};


} // graphics
