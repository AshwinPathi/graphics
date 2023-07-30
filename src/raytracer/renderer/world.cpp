#include "src/raytracer/renderer/world.h"
#include "src/math/vector3.h"

namespace {

constexpr int kDistanceCutoff = 1000;
constexpr auto float_infinity = std::numeric_limits<float>::infinity();

} // namespace


namespace graphics::raytracer {

World::World() {}

void World::AddObject(std::shared_ptr<Intersectable> object) {
  objects_.push_back(object);
}

void World::ClearObjects() {
  objects_.clear();
}

const std::vector<std::shared_ptr<Intersectable>>& World::Objects() const {
  return objects_;
}

ObjectIntersectionInfo World::Intersect(const math::Vector3& origin, const math::Vector3& direction) const {
  ObjectIntersectionInfo nearest_object{.distance = float_infinity};

  // Go through each of the objects in the scene and see if the ray starting at |origin| and in
  // direction |direction| hits any objects. Return the information of the first object
  // that was hit.
  for (const auto& object : objects_) {
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
