/*
Represents a basic plane. You can either define it by plane constants (A, B, C, D) such that
Ax + By + Cz + D = 0, or you can directly define the plane with a point and a normal vector.
*/
#pragma once

#include "src/raytracer/shapes/intersectable.h"
#include "src/math/vector3.h"
#include "src/raytracer/common/material.h"

namespace graphics::raytracer {

class Plane : public IntersectableImpl {

public:
  // Define a plane with a point and a normal
  Plane(math::Vector3 point, math::Vector3 normal, Material material);

  // Define a plane with constants for plane equation
  Plane(float a, float b, float c, float d, Material material);

  ObjectIntersectionInfo Intersect(const math::Vector3& origin, const math::Vector3& direction) const override;

public:
  // Planes can be uniquely defined by a point on the plane, and a normal to the plane.
  math::Vector3 point_{};
  math::Vector3 normal_{};
  Material material_{};
};

} // graphics::raytracer
