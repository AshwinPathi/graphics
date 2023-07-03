/*
Base class for a generic intersectable object. Intersectables implement an intersect function that returns whether
or not the shape was hit, and the properties of the intersectable if it was hit.

Shapes also implement some properties like color that the intersectable has when hit.
*/
#pragma once
#include "../../math/vector.h"
#include "shape_utils.h"

namespace graphics::raytracer {

struct ObjectIntersectionInfo {
  // Flag to determine whether or not the object was intersected with.
  bool hit;
  // Value for how far along the distance vector the intersection took place,
  // if any.
  float distance;
  // Normal vector of the hit object
  math::Vector3 normal;
};

// Alias for the failed hit struct.
constexpr ObjectIntersectionInfo kFailedHit{.hit = false, .distance = 0.0, .normal = math::ZeroVector};

class IntersectableImpl {

public:
  IntersectableImpl() = default;

  IntersectableImpl(Material material) : material{material} {}

  // Shapes must override the objectIntersect method, which calculates if the object was hit
  // and the distance along the direction vector at which the object was hit.
  virtual ObjectIntersectionInfo objectIntersect(const math::Vector3& origin, const math::Vector3& direction) const = 0;

public:
  // Intersectables have some material properties like color, reflection, etc.
  Material material;
};

} // graphics::raytracer
