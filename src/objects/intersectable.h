// Abstract object that represents an intersectable entity in the scene. Intersectable objects
// implement an intersect(ray) method that returns a metadata struct if the ray hit the object.
#pragma once

#include <optional>
#include <memory>

#include "../utils/ray.h"
#include "../math/vec.h"
#include "../materials/material.h"

namespace graphics::raytracer {

struct ObjectIntersectionInfo {
  // Value for how far along the distance vector the intersection took place,
  // if any. This is commonly referred to as 't'.
  float t;
  // Intersection point.
  math::Point3f point;
  // Normal vector of the hit object
  math::Vector3f normal;
  // The material of the object hit.
  std::shared_ptr<Material> material;
};


class Intersectable {

public:
  virtual ~Intersectable() = default;

  virtual std::optional<ObjectIntersectionInfo> Intersect(const Ray& ray) const = 0;
};

} // namespace graphics::raytracer
