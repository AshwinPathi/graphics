#include "src/raytracer/shapes/plane.h"

#include "src/raytracer/shapes/intersectable.h"
#include "src/math/vector3.h"
#include "src/math/fast_math.h"
#include "src/raytracer/common/material.h"

namespace graphics::raytracer {

Plane::Plane(math::Vector3 point, math::Vector3 normal, Material material) :
  point_{point}, normal_{normal}, material_{material} {}

Plane::Plane(float a, float b, float c, float d, Material material) : material_{material} {
  if (a != 0.0) {
    point_ = math::UnitX * (-d/a);
  } else if (b != 0.0) {
    point_ = math::UnitY * (-d/b);
  } else if (c != 0.0) {
    point_ = math::UnitZ * (-d/c);
  } else {
    point_ = math::ZeroVector;
  }
  normal_ = math::Vector3{a, b, c}.normalize();
}

ObjectIntersectionInfo Plane::Intersect(const math::Vector3& origin, const math::Vector3& direction) const {
  const float denominator = direction * normal_;
  const float num = (point_ - origin) * normal_;
  // Ray parallel to the plane, so no intersection.
  if (denominator > -1e-6 && denominator < 1e-6) {
    return kFailedHit;
  }
  const float t = ((point_ - origin) * normal_) / denominator;
  // Distance negative, no intersection.
  if (t < 0) {
    return kFailedHit;
  }
  return ObjectIntersectionInfo{.hit = true,
                                .distance = t,
                                .point = origin + direction * t,
                                .normal = normal_.normalize(),
                                .material = material_};
}


} // graphics::raytracer
