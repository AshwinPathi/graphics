/* Abstract object that represents an intersectable entity in the scene. Intersectable objects
implement an intersect(ray) method that returns a metadata struct if the ray hit the object.
*/
#pragma once

#include "../utils/ray.h"
#include "../math/vec.h"

#include <optional>
#include <memory>

namespace graphics {

struct ObjectIntersectionInfo {
  // Flag to determine whether or not the object was intersected with.
  bool hit;
  // Value for how far along the distance vector the intersection took place,
  // if any. This is commonly referred to as 't'.
  float t;
  // Intersection point.
  math::Point3f point;
  // Normal vector of the hit object
  math::Vector3f normal;
  // The material of the object hit, if any
  Material material;
};

class Intersectable {

public:
  virtual std::optional<ObjectIntersectionInfo> intersect(const Ray& ray) const = 0;
};

} // graphics
