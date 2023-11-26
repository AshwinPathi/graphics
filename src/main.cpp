#include <iostream>
#include <memory>

#include "objects/sphere.h"
#include "objects/plane.h"
#include "objects/triangle.h"
#include "objects/intersectable_list.h"
#include "objects/intersectable.h"
#include "materials/diffuse.h"
#include "utils/color.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"
#include "utils/image.h"


graphics::raytracer::Scene ConstructScene() {
  /*
  auto diffuse_red = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Red);
  auto sphere = std::make_shared<graphics::raytracer::Sphere>(graphics::math::Vector3f{0.f, 0.f, -1.f},  0.5, diffuse_red);

  auto diffuse_green = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Green);
  auto plane = std::make_shared<graphics::raytracer::Plane>(0.f, 1.f, 0.f, 0.5, diffuse_green);

  auto diffuse_blue = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Blue);
  auto plane2 = std::make_shared<graphics::raytracer::Plane>(1.f, 2.f, 0.1, 4.f, diffuse_blue);
  */

  /*
  auto diffuse_green = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Green);
  auto triangle1 = std::make_shared<graphics::raytracer::Triangle>(
    graphics::math::Vector3f{0.f, -0.6, -1.f}, graphics::math::Vector3f{-.7, .3, -1.2},
    graphics::math::Vector3f{-.7, -.7, -.8}, diffuse_green);


  auto diffuse_blue = std::make_shared<graphics::raytracer::Diffuse>(graphics::colors::Blue);
  auto triangle = std::make_shared<graphics::raytracer::Triangle>(
    graphics::math::Vector3f{0.f, -0.6, -1.f}, graphics::math::Vector3f{-.7, .3, -1.2},
    graphics::math::Vector3f{.8, .5, -0.9}, diffuse_blue);
  */

  auto intersection_list = std::make_shared<graphics::raytracer::IntersectableList>();
  //intersection_list->AddObject(triangle);
  //intersection_list->AddObject(triangle1);
  //intersection_list->AddObject(sphere);
  //intersection_list->AddObject(plane);
  //intersection_list->AddObject(plane2);


  graphics::raytracer::Scene scene {
    .background_color = graphics::Color3f{0.5, 0.7, 1.0},
    .objects = intersection_list,
  };
  return scene;
}

int main() {
  constexpr size_t height = 400;
  constexpr size_t width = 450;
  graphics::Image<height, width> image;

  constexpr graphics::raytracer::Camera camera { // Not actually a compile error
    .eye      = graphics::math::ZeroVector,
    .forward  = -graphics::math::UnitZ,
    .right    = graphics::math::UnitX,
    .up       = graphics::math::UnitY,
  };

  auto scene = ConstructScene();

  // If this becomes > 1, then we have execessive shadow because of our diffuse model.
  graphics::raytracer::RenderScene(image, camera, scene, 1);

  image.write("./test.ppm");
  return 0;
}
