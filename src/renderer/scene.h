#pragma once
#include <memory>
#include <vector>

#include "../objects/intersectables/intersectable_list.h"
#include "../objects/lights/light.h"
#include "../utils/color.h"

namespace graphics::raytracer {

// Represents the scene, like objects in the intersectable list
// any lighting elements, the sky background, etc.
struct Scene {
  std::shared_ptr<IntersectableList> objects;
  std::vector<std::shared_ptr<Light>> lights;
  Color3f background_color{};
};

} // namespace graphics::raytracer
