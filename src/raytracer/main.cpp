#include <iostream>
#include <vector>
#include <memory>

#include "../core/image.h"
#include "renderer/renderer.h"
#include "scene_parser.h"


void runRaytracer(const graphics::raytracer::SceneInfo& scene) {
  graphics::Image im(scene.height, scene.width);

  constexpr graphics::raytracer::CameraInfo camera {
    .eye = graphics::math::ZeroVector,
    .forward = -graphics::math::UnitZ,
    .right = graphics::math::UnitX,
    .up = graphics::math::UnitY,
  };

  graphics::raytracer::renderScene(im, camera, scene, 4);

  im.write("./test.ppm");
}

int main() {
  std::string location;
  std::cout << "input location: \n"; 
  std::cin >> location;
  const auto& scene = graphics::raytracer::readScene(location);
  runRaytracer(scene);
  return 0;
}
