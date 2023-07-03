/*
The main raytracer driver functions.

renderScene() is the main method that takes in camera, object, and light input to
create a signle frame of a ray traced scene.
*/
#pragma once

#include <vector>

#include "../math/vector.h"
#include "../core/color.h"
#include "../core/image.h"
#include "shapes/sphere.h"


namespace {
// These structs are in an anonymous namespace since they are only used
// in the scope of the driver.

// Bundles information about ray casting information, particularly if
// the casted ray hit anything, and the color of the object it hit (if any).
struct RayCastInfo {
  bool hit;
  graphics::Color color;
};

// Holds information about the properties of an intersected object.
struct SceneIntersectionInfo {
  // Flag to determine whether or not the object was intersected with.
  bool hit;
  // The position at which the intersection occured, if any.
  graphics::math::Vector3 position;
  // The normal vector of the intersected object.
  graphics::math::Vector3 normal;
  // The material of the object that was hit
  graphics::Material material;
};

} // namespace

namespace graphics {

// Holds information about the camera that looks into the scene.
struct CameraInfo {
  math::Vector3 eye;
  math::Vector3 forward;
  math::Vector3 right;
  math::Vector3 up;
};

// Represents a point light source that has a color.
// It is infinitely far in the direction of the |direction| vector.
struct PointLight {
  Color color;
  math::Vector3 direction;
};

// Holds information for the overall scene.
struct SceneInfo {
  // Represents shapes and structures in the scene.
  std::vector<Sphere> objects;
  // Represents the background color of the scene if nothing intersects
  // with any objects.
  Color background_color;
  // Represents a set of point light sources in the scene.
  std::vector<PointLight> point_lights;
};


// Renders a single frame a of a scene given some input parameters. Basically just calls
// castRay() in a loop over all the pixels in the scene, then outputs the image to the
// |output_image| buffer.
void renderScene(Image& output_image, const CameraInfo& camera,
                 const SceneInfo& scene, int max_depth);

// casts a ray from |origin| along |direction| into the |scene|.
// If reflections are enabled, the reflected ray will bounce at most
// |max_bounces| times.
RayCastInfo castRay(const math::Vector3& origin, const math::Vector3& direction,
          const SceneInfo& scene, int cur_depth, int max_depth);


// Finds out what object a given ray intersected with in the scene.
SceneIntersectionInfo objectIntersections(const math::Vector3& origin, const math::Vector3& direction, const SceneInfo& scene);

} // namespace graphics
