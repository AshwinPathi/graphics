// Represents a basic plane. You can either define it by plane constants (A, B, C, D) such that
// Ax + By + Cz + D = 0, or you can directly define the plane with a point and a normal vector.
#pragma once

#include <memory>
#include <optional>

#include "../objects/intersectable.h"
#include "../math/vec.h"
#include "../utils/ray.h"
#include "../materials/material.h"
#include "../math/fast_math.h"

namespace graphics::raytracer {

class Plane : public Intersectable {

public:
  // Define a plane with a point and a normal
  Plane(math::Point3f point, math::Vector3f normal, std::shared_ptr<Material> material) :
    point_{point}, normal_{normal}, material_{material} {}

  // Define a plane with constants for plane equation
  Plane(float a, float b, float c, float d, std::shared_ptr<Material> material) {
    if (a != 0.0) {
      point_ = math::UnitX * (-d/a);
    } else if (b != 0.0) {
      point_ = math::UnitY * (-d/b);
    } else if (c != 0.0) {
      point_ = math::UnitZ * (-d/c);
    } else {
      point_ = math::ZeroVector;
    }
    normal_ = normalize(math::Vector3f{a, b, c});
    material_ = material;
  }

  std::optional<ObjectIntersectionInfo> Intersect(const Ray& ray) const override {
    const float denominator = ray.direction() * normal_;
    const float num = (point_ - ray.origin()) * normal_;
    // Ray parallel to the plane, so no intersection.
    if (denominator > -1e-6 && denominator < 1e-6) {
      return std::nullopt;
    }
    const float t = ((point_ - ray.origin()) * normal_) / denominator;
    // Distance negative, no intersection.
    if (t < 0) {
      return std::nullopt;
    }
    return ObjectIntersectionInfo{.t = t,
                                  .point = ray.at(t),
                                  .normal = normalize(normal_),
                                  .material = material_};
  }

public:
  math::Vector3f point_{};
  math::Vector3f normal_{};
  std::shared_ptr<Material> material_{};
};

} // graphics::raytracer
