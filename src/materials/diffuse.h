// Generic diffuse object.
#pragma once

#include <optional>

#include "material.h"
#include "../utils/color.h"
#include "../objects/intersectable.h"

namespace graphics::raytracer {

class Diffuse : public Material {

public:
  Diffuse(const Color3f& color) : color_{color} {}

  std::optional<ScatterInfo> Scatter(const Ray& ray_in, const ObjectIntersectionInfo& intersection_info) const override {
    return ScatterInfo{.ray_out = ray_in, .attenuation = color_};
  }

private:
  Color3f color_{};
};

} // namespace graphics::raytracer
