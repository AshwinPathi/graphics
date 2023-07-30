#include "src/raytracer/renderer/renderer.h"

#include <vector>
#include <memory>

#include "src/math/vector3.h"
#include "src/core/color.h"
#include "src/core/ppm_image.h"
#include "src/raytracer/common/material.h"
#include "src/raytracer/renderer/renderer_utils.h"


namespace {

constexpr int kDistanceCutoff = 1000;
constexpr float kBias = 0.0001;
constexpr auto float_infinity = std::numeric_limits<float>::infinity();

}

namespace graphics::raytracer {

void RenderScene(PPMImage& output_image, const CameraInfo& camera,
                 const SceneInfo& scene, int max_depth) {
  // Have to cast to an integer since this will mess up negative division.
  const int H = static_cast<int>(output_image.height());
  const int W = static_cast<int>(output_image.width());

  // Basic loop for rendering - go through every pixel in the scene, cast
  // a ray from it, and see what color it is. Assign that color to the
  // pixel we just shot a ray from.
  // TODO - this can be trivially parallelized, consider using some threadpool
  // implementation to batch each row of parsing.
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      const float sx = (2 * x - W) / (float) std::max(W, H);
      const float sy = (H - 2 * y) / (float) std::max(W, H);

      const math::Vector3 origin = camera.eye;
      const math::Vector3 direction = (camera.forward + camera.right * sx + camera.up * sy).normalize();

      const auto& ray_cast_info = CastRay(origin, direction, scene, 0, max_depth);

      output_image[y][x] = ray_cast_info.color;
    }
  }
}

RayCastInfo CastRay(const math::Vector3& origin, const math::Vector3& direction,
          const SceneInfo& scene, int cur_depth, int max_depth) {
  // First check to see if we hit any object in the scene, given a ray starting at |origin|
  // and looking in direction |direction|.
  const auto& intersected_object = Intersections(origin, direction, scene);
 
  // If we don't hit anything, then return a failed hit and the background color.
  if (cur_depth >= max_depth || !intersected_object.hit) {
    return RayCastInfo{.hit = false, .color = scene.background_color};
  }

  Color ray_color{0.0, 0.0, 0.0};
  for (const auto& light_source : scene.point_lights) {
    // If we were using different light sources here, then this would change.
    // Since we assume point light sources are already encoded by the direction
    // they are in, we don't need to do any additional processing.
    const auto& direction_to_light = light_source.direction;

    // Checks to see if there is any intersection between the object we just hit, and the light source.
    // Note that the shadow ray origin has to be slightly offset to prevent "shadow acne"
    const auto& shadow_ray_origin = intersected_object.point + (intersected_object.normal * kBias);
    const auto& light_obj_intersection = Intersections(shadow_ray_origin, direction_to_light.normalize(), scene);

    // If we hit an object on the way to the light, then this spot is not illuminated, and we can continue the
    // rest of the loop.
    if (light_obj_intersection.hit) {
      continue;
    }
    // Intensity is hard coded to be 1.0 for point light sources
    const float intensity = 1.0;

    // Sum up the colors from each light source
    const auto lighting_multiplier = std::max(0.f, (intersected_object.normal * direction_to_light.normalize())) * intensity;
    ray_color += intersected_object.material.color * light_source.color * lighting_multiplier;
  }

  return RayCastInfo{.hit = true, .color = ray_color};
}


ObjectIntersectionInfo Intersections(const math::Vector3& origin, const math::Vector3& direction, const SceneInfo& scene) {
  ObjectIntersectionInfo nearest_object{.distance = float_infinity};

  // Go through each of the objects in the scene and see if the ray starting at |origin| and in
  // direction |direction| hits any objects. Return the information of the first object
  // that was hit.
  for (const auto& object : scene.objects) {
    auto object_intersection = object->Intersect(origin, direction);
    if (!object_intersection.hit || object_intersection.distance > nearest_object.distance) {
      continue;
    }
    nearest_object = std::move(object_intersection);
  }

  nearest_object.hit = nearest_object.distance < kDistanceCutoff;
  return nearest_object;
}

} // graphics::raytracer
