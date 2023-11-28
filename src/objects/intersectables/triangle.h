// Triangle: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html
#pragma once

#include <memory>
#include <optional>

#include "../../objects/intersectables/intersectable.h"
#include "../../math/vec.h"
#include "../../utils/ray.h"
#include "../../materials/material.h"
#include "../../math/fast_math.h"

namespace graphics::raytracer {

class Triangle : public Intersectable {

public:
  // Define a plane with a point and a normal
  Triangle(math::Point3f v0, math::Point3f v1, math::Point3f v2, std::shared_ptr<Material> material) :
    v0_{v0}, v1_{v1}, v2_{v2}, material_{material} {}

  std::optional<ObjectIntersectionInfo> Intersect(const Ray& ray) const override {
    math::Vector3f v0v1 = v1_ - v0_;
    math::Vector3f v0v2 = v2_ - v0_;

    math::Vector3f N = cross(v0v1, v0v2);
    float area = magnitude(N);

    // check if the ray and plane are parallel.
    float NdotRayDirection = N * ray.direction();
    if (std::fabs(NdotRayDirection) < 0.001) // almost 0
      return std::nullopt; // they are parallel, so they don't intersect! 

    // compute d parameter using equation 2
    float d = -N * v0_;
    
    // compute t (equation 3)
    float t = -(N * ray.origin() + d) / NdotRayDirection;
    
    // check if the triangle is behind the ray
    if (t < 0) return std::nullopt; // the triangle is behind
 
    // compute the intersection point using equation 1
    math::Vector3f P = ray.origin() + t * ray.direction();
 
    // Step 2: inside-outside test
    math::Vector3f C; // vector perpendicular to triangle's plane
 
    // edge 0
    math::Vector3f edge0 = v1_ - v0_; 
    math::Vector3f vp0 = P - v0_;
    C = cross(edge0, vp0);
    if (N * C < 0) return std::nullopt; // P is on the right side
 
    // edge 1
    math::Vector3f edge1 = v2_ - v1_;
    math::Vector3f vp1 = P - v1_;
    C = cross(edge1, vp1);
    if (N * C < 0)  return std::nullopt; // P is on the right side
 
    // edge 2
    math::Vector3f edge2 = v0_ - v2_; 
    math::Vector3f vp2 = P - v2_;
    C = cross(edge2, vp2);
    if (N * C < 0) return std::nullopt; // P is on the right side;

    return ObjectIntersectionInfo{.t = t,
                                  .point = ray.at(t),  // this ray hits the triangle
                                  .normal = normalize(N),
                                  .material = material_};
  }

public:
  // the three vertices of the triangle
  math::Point3f v0_;
  math::Point3f v1_;
  math::Point3f v2_;
  std::shared_ptr<Material> material_{};
};

} // graphics::raytracer
