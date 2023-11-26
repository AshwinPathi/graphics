#pragma once
#include <memory>

#include "../objects/intersectable_list.h"
#include "../utils/color.h"

namespace graphics::raytracer {

// Represents the scene, like objects in the intersectable list
// any lighting elements, the sky background, etc.
struct Scene {
  std::shared_ptr<IntersectableList> objects;
  Color3f background_color;
  // TOOD Lighting objects go here
};

} // namespace graphics::raytracer
