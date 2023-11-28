// Generic diffuse object.
#pragma once

#include <optional>

#include "../materials/material.h"
#include "../math/vec_utils.h"
#include "../math/vec.h"
#include "../utils/ray.h"
#include "../utils/color.h"
#include "../objects/intersectables/intersectable.h"

namespace graphics::raytracer {

class Diffuse : public Material {

public:
  Diffuse(const Color3f& color) : color_{color} {}

  std::optional<ScatterInfo> Scatter(const Ray& ray_in, const ObjectIntersectionInfo& intersection_info) const override {
    math::Vector3f scatter_direction = intersection_info.normal;
    if (math::near_zero(scatter_direction)) {
      scatter_direction = intersection_info.normal;
    }
    auto scatter_ray = Ray(intersection_info.point + (0.0001f * scatter_direction), scatter_direction);
    return ScatterInfo{.ray_out = scatter_ray, .attenuation = color_};
  }

private:
  Color3f color_{};
};

} // namespace graphics::raytracer
