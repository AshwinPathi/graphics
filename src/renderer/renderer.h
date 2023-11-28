#pragma once

#include "../math/vec.h"
#include "../utils/ray.h"
#include "../utils/image.h"
#include "../renderer/camera.h"
#include "../renderer/scene.h"

namespace {

constexpr float kBias = 0.0001f;

} // namespace

namespace graphics::raytracer {

Color3f castRay(const Ray& ray, const Scene& scene, [[maybe_unused]] int cur_depth) {
  Color3f ray_color = Color3f{0.f, 0.f, 0.f};

  // Check to see if this ray intersects anything at all
  if (auto intersect_result = scene.objects->Intersect(ray)) {
    // Then check to see if this ray scatters any light (by default it will)
    auto scatter_result = intersect_result->material->Scatter(ray, *intersect_result);

    // attenuation is the color of the diffuse component of the hit object.
    auto diffuse_color = scatter_result->attenuation;

    bool in_shadow = false;
    for (const auto light : scene.lights) {
 
      math::Vector3f dir_to_light_norm = normalize(light->Direction(intersect_result->point));
      Ray shadow_ray{intersect_result->point + (kBias * intersect_result->normal), dir_to_light_norm};

      if (auto shadow_result = scene.objects->Intersect(shadow_ray); !shadow_result.has_value()) {
        float shadow_multiplier = std::max(0.f, intersect_result->normal * dir_to_light_norm);
        Color3f lighting_multiplier = light->Color() * light->Intensity(intersect_result->point);
        ray_color += elem_prod(diffuse_color, lighting_multiplier * shadow_multiplier);
      }
    }
    return ray_color;
  }

  // Make the background sky color look pretty by making it a gradient.
  math::Vector3f unit = normalize(ray.direction());
  float a = 0.5 * (unit.y + 1.0);
  return (1.f - a) * Color3f{1.f, 1.f, 1.f} + a * scene.background_color;
}


Ray getCameraRay(const Camera& camera, int x, int y, int H, int W) {
  const float sx = (2 * x - W) / static_cast<float>(std::max(W, H));
  const float sy = (H - 2 * y) / static_cast<float>(std::max(W, H));

  const math::Vector3f origin = camera.eye;
  const math::Vector3f direction = math::normalize(camera.forward + camera.right * sx + camera.up * sy);

  return Ray{origin, direction};
}


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
      const Ray ray = getCameraRay(camera, x, y, height, width);
      // Make sure the color is within 0 - 1.
      const Color3f color = clamp_color3f(castRay(ray, scene, max_depth));
      output_image.set_pixel(color, y, x);
    }
  }
}

} // namespace graphics::raytracer
