#include <iostream>
#include <vector>

#include "src/core/image.h"
#include "src/raytracer/driver.h"
#include "src/raytracer/shapes/sphere.h"


namespace {

constexpr size_t kImageHeight = 300;
constexpr size_t kImageWidth = 400;

}

graphics::SceneInfo createScene() {
  // Add some lights to the scene.
  std::vector<graphics::PointLight> lights;
  graphics::PointLight source1 {
      .color = {1., 1., 1.},
      .direction = {.x = 1.0, .y = 1.0, .z = 1.0}
  };
  lights.push_back(source1);

  // Add some objects to the scene.
  std::vector<graphics::Sphere> objects;

  graphics::Sphere sphere{
    graphics::math::Vector3{.x = 0.0, .y = 0.0, .z = -1.0},
    0.3,
    graphics::Material{
      graphics::Color{1.0, 0.0, 0.0}
    }
  };
  objects.push_back(sphere);

  graphics::Sphere sphere2{
    graphics::math::Vector3{.x = 1., .y = 0.8, .z = -1.0},
    0.5,
    graphics::Material{
      graphics::Color{0.0, 1.0, 0.0}
    }
  };
  objects.push_back(sphere2);

  // Construct the scene.
  graphics::SceneInfo scene {
    .objects = std::move(objects),
    .background_color = graphics::Color{0.5, 0.5, 1.0},
    .point_lights = std::move(lights)
  };

  return scene;
}

void runRaytracer() {
  graphics::Image im(kImageHeight, kImageWidth);

  constexpr graphics::CameraInfo camera {
    .eye = graphics::math::ZeroVector,
    .forward = -graphics::math::UnitZ,
    .right = graphics::math::UnitX,
    .up = graphics::math::UnitY,
  };

  const auto& scene = createScene();

  graphics::renderScene(im, camera, scene, 4);

  im.write("./test.ppm");
}


int main() {
  runRaytracer();

  return 0;
}
