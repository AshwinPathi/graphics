#include "src/raytracer/shapes/sphere.h"

#include "src/raytracer/shapes/intersectable.h"
#include "src/math/vector3.h"
#include "src/math/fast_math.h"
#include "src/raytracer/common/material.h"

namespace graphics::raytracer {

Sphere::Sphere(math::Vector3 center, float radius, Material material) :
  center_{center}, radius_{radius}, material_{material} {} 


ObjectIntersectionInfo Sphere::Intersect(const math::Vector3& origin, const math::Vector3& direction) const {
  // Check to see if the intersection is inside the sphere or not.
  const bool inside = (center_ - origin).magnitudesq() < radius_ * radius_;

  const float tc = ((center_ - origin) * direction) / direction.magnitude();

  // This means we had no intersection with the sphere.
  if (!inside && tc < 0) {
      return kFailedHit;
  }

  // Once again, no intersection with the sphere.
  const float dd = (origin + direction * tc - center_).magnitudesq();
      if (!inside and dd > radius_ * radius_) {
      return kFailedHit;
  }

  const float t_offset = math::sqrt(radius_ * radius_ - dd) / direction.magnitude();
  float t = tc + (inside ? t_offset : -t_offset);
  return ObjectIntersectionInfo{.hit = true,
                                .distance = t,
                                .point = origin + direction * t,
                                .normal = ((origin + direction * t) - center_).normalize(),
                                .material = material_};
}

} // graphics::raytracer
