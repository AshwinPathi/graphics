/*
Base class for a generic shape. Shapes implement an intersect function that returns whether
or not the shape was hit, and the properties of the shape if it was hit.

Shapes also implement some properties like color that the shape has when hit.
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

struct ShapeImpl {
  // Shapes have some material properties like color, reflection, etc.
  Material material;

  ShapeImpl() = default;

  ShapeImpl(Material material) : material{material} {}

  // Shapes must override the objectIntersect method, which calculates if the object was hit
  // and the distance along the direction vector at which the object was hit.
  virtual ObjectIntersectionInfo objectIntersect(const math::Vector3& origin, const math::Vector3& direction) const = 0;
};


} // graphics::raytracer
