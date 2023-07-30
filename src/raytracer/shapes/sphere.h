// Represents a basic sphere.
#pragma once

#include "src/raytracer/shapes/intersectable.h"
#include "src/raytracer/shapes/sphere.h"
#include "src/raytracer/common/material.h"
#include "src/math/vector3.h"

namespace graphics::raytracer {

class Sphere : public Intersectable {

public:
  Sphere(math::Vector3 center, float radius, Material material);

  ObjectIntersectionInfo Intersect(const math::Vector3& origin, const math::Vector3& direction) const override;

public:
  // You can uniquely define a sphere with the center and its radius (and the material properties)
  // inhereted from an intersectable object.
  math::Vector3 center_{};
  float radius_{};
  Material material_{};
};

} // graphics::raytracer
