/*
Defines useful renderer structs.
*/
#pragma once
#include <memory>
#include <vector>

#include "src/math/vector3.h"
#include "src/core/color.h"
#include "src/raytracer/shapes/intersectable.h"

namespace graphics::raytracer {

// Holds information about the camera that looks into the scene.
struct CameraInfo {
  math::Vector3 eye;
  math::Vector3 forward;
  math::Vector3 right;
  math::Vector3 up;
};

// Represents a point light source that has a color.
// It is infinitely far in the direction of the |direction| vector.
struct PointLight {
  Color color;
  math::Vector3 direction;
};

// Holds information for the overall scene.
struct SceneInfo {
  // Scene height
  size_t height;
  // Scene width;
  size_t width;
  // Represents shapes and structures in the scene.
  std::vector<std::shared_ptr<IntersectableImpl>> objects;
  // Represents the background color of the scene if nothing intersects
  // with any objects.
  Color background_color;
  // Represents a set of point light sources in the scene.
  std::vector<PointLight> point_lights;
};

} // graphics::raytracer
