#include <iostream>
#include <vector>
#include <memory>

#include "src/core/ppm_image.h"
#include "src/raytracer/renderer/renderer.h"
#include "src/raytracer/utils/scene_parser.h"


void runRaytracer(const graphics::raytracer::SceneInfo& scene, int num_threads) {
  graphics::PPMImage im(scene.height, scene.width);

  constexpr graphics::raytracer::CameraInfo camera {
    .eye = graphics::math::ZeroVector,
    .forward = -graphics::math::UnitZ,
    .right = graphics::math::UnitX,
    .up = graphics::math::UnitY,
  };

  graphics::raytracer::FastRenderScene(im, camera, scene, 4, num_threads);

  im.Write("./test.ppm");
}

int main() {
  std::string location;
  int num_threads;
  std::cout << "input location: \n"; 
  std::cin >> location;
  std::cout << "Number of threads: \n";
  std::cin >> num_threads;
  const auto& scene = graphics::raytracer::ReadScene(location);
  runRaytracer(scene, num_threads);
  return 0;
}
