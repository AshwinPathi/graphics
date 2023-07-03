/*
Represents a basic plane. You can either define it by plane constants (A, B, C, D) such that
Ax + By + Cz + D = 0, or you can directly define the plane with a point and a normal vector.
*/
#pragma once

#include "shape.h"
#include "../../math/vector.h"
#include "../../math/fast_math.h"
#include "shape_utils.h"

namespace graphics::raytracer {

struct Plane : ShapeImpl {
  math::Vector3 point;
  math::Vector3 normal;
  Material material;

  Plane() = default;

  Plane(math::Vector3 point_in, math::Vector3 normal_in, Material material_in) : point{point_in}, normal{normal_in}, ShapeImpl{material_in} {}

  Plane(float a, float b, float c, float d, Material material_in) : ShapeImpl{material_in} {
    if (a != 0.0) {
      point = math::UnitX * (-d/a);
    } else if (b != 0.0) {
      point = math::UnitY * (-d/b);
    } else if (c != 0.0) {
      point = math::UnitZ * (-d/c);
    } else {
      point = math::ZeroVector;
    }
    normal = math::Vector3{a, b, c}.normalize();
  }

  ObjectIntersectionInfo objectIntersect(const math::Vector3& origin, const math::Vector3& direction) const override {
    const float denominator = direction * normal;
    const float num = (point - origin) * normal;
    // Ray parallel to the plane, so no intersection.
    if (denominator > -1e-6 && denominator < 1e-6) {
      return ObjectIntersectionInfo{.hit = false, .distance = 0, .normal = math::ZeroVector};
    }
    const float t = ((point - origin) * normal) / denominator;
    // Distance negative, no intersection.
    if (t < 0) {
      return ObjectIntersectionInfo{.hit = false, .distance = 0, .normal = math::ZeroVector};
    }
    return ObjectIntersectionInfo{.hit = true, .distance = t, .normal = normal.normalize()};
  }
};


} // graphics::raytracer
