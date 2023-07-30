#include <iostream>
#include <vector>
#include <memory>

#include "src/core/ppm_image.h"
#include "src/raytracer/renderer/renderer.h"
#include "src/raytracer/utils/scene_parser.h"


void runRaytracer(const graphics::raytracer::SceneInfo& scene) {
  graphics::PPMImage im(scene.height, scene.width);

  constexpr graphics::raytracer::CameraInfo camera {
    .eye = graphics::math::ZeroVector,
    .forward = -graphics::math::UnitZ,
    .right = graphics::math::UnitX,
    .up = graphics::math::UnitY,
  };

  graphics::raytracer::RenderScene(im, camera, scene, 4);

  im.Write("./test.ppm");
}

int main() {
  std::string location;
  std::cout << "input location: \n"; 
  std::cin >> location;
  const auto& scene = graphics::raytracer::ReadScene(location);
  runRaytracer(scene);
  return 0;
}
