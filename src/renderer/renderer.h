#pragma once

#include "../math/vec.h"
#include "../utils/ray.h"
#include "../utils/image.h"
#include "camera.h"
#include "scene.h"

namespace graphics::raytracer {

// TODO - remove these annoying forward declarations
Color3f CastRay(const Ray& ray, const Scene& scene, int cur_depth);
Ray getCameraRay(const Camera& camera, int x, int y, int H, int W);


// Template here to pass in templated image
// TODO maybe remove
template <size_t H, size_t W>
void RenderScene(Image<H, W>& output_image, const Camera& camera, const Scene& scene, int max_depth) {
  // Have to cast to an integer since this will mess up negative division.
  const int height = static_cast<int>(output_image.height());
  const int width = static_cast<int>(output_image.width());

  // Basic loop for rendering - go through every pixel in the scene, cast
  // a ray from it, and see what color it is. Assign that color to the
  // pixel we just shot a ray from.
  // TODO - this can be trivially parallelized, consider using some threadpool
  // implementation to batch each row of parsing.
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      const auto ray = getCameraRay(camera, x, y, height, width);
      const auto color = CastRay(ray, scene, max_depth);
      output_image.set_pixel(color, y, x);
    }
  }
}

Color3f CastRay(const Ray& ray, const Scene& scene, int cur_depth) {
  if (cur_depth <= 0) {
    return colors::White;
  }
  if (auto intersect_result = scene.objects->Intersect(ray)) {
    if (auto scatter_result = intersect_result->material->Scatter(ray, *intersect_result)) {
      auto attenuation = scatter_result->attenuation;
      // TODO eliminate recursive call and use iteration instead
      auto casted_ray = CastRay(scatter_result->ray_out, scene, cur_depth - 1);
      return Color3f{
        attenuation.r * casted_ray.r,
        attenuation.g * casted_ray.g,
        attenuation.b * casted_ray.b
      };
    }
    return colors::Black;
  }
  return scene.background_color;
}

Ray getCameraRay(const Camera& camera, int x, int y, int H, int W) {
  const float sx = (2 * x - W) / static_cast<float>(std::max(W, H));
  const float sy = (H - 2 * y) / static_cast<float>(std::max(W, H));

  const math::Vector3f origin = camera.eye;
  const math::Vector3f direction = math::normalize(camera.forward + camera.right * sx + camera.up * sy);

  return Ray{origin, direction};
}

} // namespace graphics::raytracer
