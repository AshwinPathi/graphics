#pragma once

#include "../math/vec.h"

namespace graphics::raytracer {

// Represennts the geometry of the camera that the scene will be rendered from the
// perspective of.
struct Camera {
  math::Vector3f eye;
  math::Vector3f forward;
  math::Vector3f right;
  math::Vector3f up;
};

} // namespace graphics::raytracer
