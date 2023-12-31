#include <iostream>
#include <memory>

#include "utils/scene_parser.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"
#include "utils/image.h"

graphics::raytracer::Scene ConstructScene(std::string_view path) {
  graphics::raytracer::SceneParser scene_parser;
  auto scene = scene_parser.ReadScene(path);
  return scene;
}

int main(int argc, char** argv) {
  constexpr size_t height = 400;
  constexpr size_t width = 400;
  graphics::Image image(height, width);

  constexpr graphics::raytracer::Camera camera { // Not actually a compile error
    .eye      = graphics::math::Vector3f{0, 0, 1}, //graphics::math::ZeroVector,
    .forward  = -graphics::math::UnitZ,
    .right    = graphics::math::UnitX,
    .up       = graphics::math::UnitY,
  };

  if (argc != 2) {
    std::cout << "Missing input scene argument.\n";
    return 0;
  }

  auto scene = ConstructScene(argv[1]);

  // If this becomes > 1, then we have execessive shadow because of our diffuse model.
  graphics::raytracer::RenderSceneMultithreaded(image, camera, scene, 1);

  image.write("./test.ppm");
  return 0;
}
