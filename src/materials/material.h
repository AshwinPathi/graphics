// Implementation of the interface that all materials must adhere to.
// Materials must implement a scatter function that returns a vector,
// if any, in the direction that the incoming light scatters to upon
// hitting the surface of the material.
#pragma once

#include <optional>

#include "../utils/ray.h"
#include "../utils/color.h"

namespace graphics::raytracer {

// Forward declaration to prevent recursive inclusion.
struct ObjectIntersectionInfo;

// Metadata about the scattered ray that is outputted from Scatter.
struct ScatterInfo {
  // Direction where light bounces off the object
  Ray ray_out;
  // The attenuation multiplicitavely changes the light being bounced off the object.
  Color3f attenuation;
};


class Material {

public:
  virtual ~Material() = default;

  virtual std::optional<ScatterInfo> Scatter(const Ray& ray_in, const ObjectIntersectionInfo& intersection_info) const = 0;
};

} // namespace graphics::raytracer
