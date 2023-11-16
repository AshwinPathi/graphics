/*
The main raytracer driver functions.

renderScene() is the main method that takes in camera, object, and light input to
create a signle frame of a ray traced scene.
*/
#pragma once

#include <vector>
#include <memory>

#include "src/math/vector3.h"
#include "src/core/color.h"
#include "src/core/ppm_image.h"
#include "src/raytracer/common/material.h"

#include "src/raytracer/renderer/renderer_utils.h"

namespace graphics::raytracer {

// Bundles information about ray casting information, particularly if
// the casted ray hit anything, and the color of the object it hit (if any).
struct RayCastInfo {
  bool hit;
  graphics::Color color;
};

// Render Scene but faster by using threading.
void FastRenderScene(PPMImage& output_image, const CameraInfo& camera,
                 const SceneInfo& scene, int max_depth, int num_threads);

void FastRenderSceneHelper(PPMImage& output_image, int min_height, int max_height, const CameraInfo& camera,
                 const SceneInfo& scene, int max_depth);

// Renders a single frame a of a scene given some input parameters. Basically just calls
// castRay() in a loop over all the pixels in the scene, then outputs the image to the
// |output_image| buffer.
void RenderScene(PPMImage& output_image, const CameraInfo& camera,
                 const SceneInfo& scene, int max_depth);

// casts a ray from |origin| along |direction| into the |scene|.
// If reflections are enabled, the reflected ray will bounce at most
// |max_bounces| times.
RayCastInfo CastRay(const math::Vector3& origin, const math::Vector3& direction,
          const SceneInfo& scene, int cur_depth, int max_depth);

} // namespace graphics
