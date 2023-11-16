// Represents a world of intersectable objects, which implements Intersectable.
// Other intersectable objects can be added to the World and when Intersect() is called
// on the world, it will return the first object that was hit by the incoming ray.
#pragma once

#include <memory>
#include <vector>

#include "src/raytracer/shapes/intersectable.h"
#include "src/math/vector3.h"

namespace graphics::raytracer {

class World : public Intersectable {

public:
  // Set up the world object.
  World();

  // Add objects to the world
  void AddObject(std::shared_ptr<Intersectable> object);

  // Clear objects from the world.
  void ClearObjects();

  const std::vector<std::shared_ptr<Intersectable>>& Objects() const;

  // Intersect the ray with all objects in the world, returning the data for the first
  // object hit.
  ObjectIntersectionInfo Intersect(const math::Vector3& origin, const math::Vector3& direction) const override;

public:
  std::vector<std::shared_ptr<Intersectable>> objects_;
};

} // graphics::raytracer
