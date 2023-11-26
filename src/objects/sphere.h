// Defines a basic sphere object to render in the scene.
#pragma once

#include <optional>

#include "../objects/intersectable.h"
#include "../math/vec.h"
#include "../utils/ray.h"
#include "../materials/material.h"
#include "../math/fast_math.h"

namespace graphics::raytracer {

class Sphere : public Intersectable {

public:
  Sphere(math::Point3f center, float radius, std::shared_ptr<Material> material) :
    center_{center}, radius_{radius}, material_{material} {}

  std::optional<ObjectIntersectionInfo> Intersect(const Ray& ray) const override {
    const auto rad_sq = radius_ * radius_;
    const bool inside = magnitude_sq(center_ - ray.origin()) < rad_sq;

    const float tc = ((center_ - ray.origin()) * ray.direction()) / magnitude(ray.direction());

    // This means we had no intersection with the sphere.
    if (!inside && tc < 0) {
      return std::nullopt;
    }

    const float dd = magnitude_sq(ray.at(tc) - center_);
    // Once again, no intersection with the sphere.
    if (!inside && dd > rad_sq) {
      return std::nullopt;
    }

    const float t_offset = math::sqrt(rad_sq - dd) / magnitude(ray.direction());
  
    // Make sure the normal is a point thats outside of the sphere
    float t = tc + (inside ? t_offset : -t_offset);

    return ObjectIntersectionInfo{.t = t,
                                  .point = ray.at(t),
                                  .normal = normalize(ray.at(t) - center_),
                                  .material = material_};
  }

public:
  math::Vector3f center_{};
  float radius_{};
  std::shared_ptr<Material> material_{};
};

} // graphics::raytracer
