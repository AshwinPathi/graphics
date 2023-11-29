#pragma once

#include <thread>

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

    for (const auto& light : scene.lights) {
 
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
void RenderSceneHelper(Image& output_image, const Camera& camera, const Scene& scene,
                       int min_height, int max_height, int max_depth) {
  // Have to cast to an integer since this will mess up negative division.
  const int height = static_cast<int>(output_image.height());
  const int width = static_cast<int>(output_image.width());

  // Basic loop for rendering - go through every pixel in the scene, cast
  // a ray from it, and see what color it is. Assign that color to the
  // pixel we just shot a ray from.
  for (int y = min_height; y < max_height; y++) {
    for (int x = 0; x < width; x++) {
      const Ray ray = getCameraRay(camera, x, y, height, width);
      // Make sure the color is within 0 - 1.
      const Color3f color = clamp_color3f(castRay(ray, scene, max_depth));
      output_image.set_pixel(color, y, x);
    }
  }
}

void RenderSceneMultithreaded(Image& output_image, const Camera& camera, const Scene& scene, int max_depth) {
  constexpr int num_threads = 8;

  const int height = static_cast<int>(output_image.height());
  const int chunk_size = height / num_threads;

  std::vector<std::thread> threads(num_threads);
  // Begin executing our fast render subprocess on each thread
  for (int i = 0; i < num_threads; i++) {
    int start_index = i * chunk_size;
    int end_index = (i == num_threads - 1 ? height : (i + 1) * chunk_size);
    // Note that output image is passed in by reference since we need each thread
    // to modify the image buffer directly.
    threads[i] = std::thread(RenderSceneHelper, std::ref(output_image), camera, scene, start_index, end_index, max_depth);
  }
  // Stop the threads by joining them all
  for (int i = 0; i < num_threads; i++) {
    threads[i].join();
  }
}

void RenderScene(Image& output_image, const Camera& camera, const Scene& scene, int max_depth) {
  const int height = static_cast<int>(output_image.height());
  RenderSceneHelper(output_image, camera, scene, 0, height, max_depth);
}

} // namespace graphics::raytracer
