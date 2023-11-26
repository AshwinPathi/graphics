#include <iostream>
#include <memory>

#include "objects/sphere.h"
#include "objects/plane.h"
#include "objects/intersectable_list.h"
#include "objects/intersectable.h"
#include "materials/diffuse.h"
#include "utils/color.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"
#include "utils/image.h"

/*
sphere 0 0 -1 0.5
plane 0 1 0 0.5
plane 1 2 0.1 4
*/

graphics::raytracer::Scene ConstructScene() {
  auto diffuse_red = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Red);
  auto sphere = std::make_shared<graphics::raytracer::Sphere>(graphics::math::Vector3f{0.f, 0.f, -1.f},  0.5, diffuse_red);

  auto diffuse_green = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Green);
  auto plane = std::make_shared<graphics::raytracer::Plane>(0.f, 1.f, 0.f, 0.5, diffuse_green);

  auto diffuse_blue = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Blue);
  auto plane2 = std::make_shared<graphics::raytracer::Plane>(1.f, 2.f, 0.1, 4.f, diffuse_blue);


  auto intersection_list = std::make_shared<graphics::raytracer::IntersectableList>();
  intersection_list->AddObject(sphere);
  intersection_list->AddObject(plane);
  intersection_list->AddObject(plane2);


  graphics::raytracer::Scene scene {
    .background_color = graphics::Color3f{0.5, 0.7, 1.0},
    .objects = intersection_list,
  };
  return scene;
}

int main() {
  constexpr size_t height = 500;
  constexpr size_t width = 500;
  graphics::Image<height, width> image;

  constexpr graphics::raytracer::Camera camera { // Not actually a compile error
    .eye      = graphics::math::ZeroVector,
    .forward  = -graphics::math::UnitZ,
    .right    = graphics::math::UnitX,
    .up       = graphics::math::UnitY,
  };

  auto scene = ConstructScene();

  graphics::raytracer::RenderScene(image, camera, scene, 1);

  image.write("./test.ppm");
  return 0;
}
