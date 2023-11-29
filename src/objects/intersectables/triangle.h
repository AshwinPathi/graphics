// Triangle: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html
#pragma once

#include <memory>
#include <optional>

#include "../../utils/vertex.h"
#include "../../objects/intersectables/intersectable.h"
#include "../../math/vec.h"
#include "../../utils/ray.h"
#include "../../materials/material.h"
#include "../../math/fast_math.h"

namespace graphics::raytracer {

class Triangle : public Intersectable {

public:
  // Define a plane with a point and a normal
  Triangle(Vertexff v0, Vertexff v1, Vertexff v2, std::shared_ptr<Material> material) :
    v0_{v0}, v1_{v1}, v2_{v2}, material_{material} {
      math::Vector3f v0v1 = v1_.point - v0_.point;
      math::Vector3f v0v2 = v2_.point - v0_.point;
      // no need to normalize
      triangle_plane_normal_ = math::cross(v0v1, v0v2);

      // To invert the normal vector
      if (triangle_plane_normal_ * v0_.point > 0) {
        normal_sign_ = -1;
      }
    }

  std::optional<ObjectIntersectionInfo> Intersect(const Ray& ray) const override {
    auto v0 = v0_.point;
    auto v1 = v1_.point;
    auto v2 = v2_.point;

    float denom = triangle_plane_normal_ * triangle_plane_normal_;

    // Step 1: finding P

    // check if the ray and plane are parallel.
    float NdotRayDirection = triangle_plane_normal_ * ray.direction();
    if (fabs(NdotRayDirection) < 0.001) // almost 0
        return std::nullopt; // they are parallel so they don't intersect! 

    // compute d parameter using equation 2
    float d = -triangle_plane_normal_ * v0;
    
    // compute t (equation 3)
    float t = -(triangle_plane_normal_ * ray.origin() + d) / NdotRayDirection;
    // check if the triangle is behind the ray
    if (t < 0) return std::nullopt; // the triangle is behind
 
    // compute the intersection point using equation 1
    math::Vector3f P = ray.origin() + t * ray.direction();
 
    // Step 2: inside-outside test
    math::Vector3f C; // vector perpendicular to triangle's plane
 
    // edge 0
    math::Vector3f edge0 = v1 - v0; 
    math::Vector3f vp0 = P - v0;
    C = math::cross(edge0, vp0);
    if (triangle_plane_normal_ * C < 0) return std::nullopt; // P is on the right side
 
    // edge 1
    float u;
    math::Vector3f edge1 = v2 - v1; 
    math::Vector3f vp1 = P - v1;
    C = math::cross(edge1, vp1);
    if ((u = triangle_plane_normal_ * C) < 0)  return std::nullopt; // P is on the right side
 
    // edge 2
    float v;
    math::Vector3f edge2 = v0 - v2; 
    math::Vector3f vp2 = P - v2;
    C = math::cross(edge2, vp2);
    if ((v = triangle_plane_normal_ * C) < 0) return std::nullopt; // P is on the right side;

    u /= denom;
    v /= denom;

    return ObjectIntersectionInfo{.t = t,
                                  .point = ray.at(t),  // this ray hits the triangle
                                  .normal = normal_sign_ * normalize(interpolateNormal(u, v, 1 - u - v)),
                                  .material = material_};
  }

private:
  math::Vector3f interpolateNormal(float u, float v, float w) const {
    if (!v0_.normal || !v1_.normal || !v2_.normal) {
      return triangle_plane_normal_;
    }
    return u * (*v0_.normal) + v * (*v1_.normal) + w * (*v2_.normal);
  }

  // the three vertices of the triangle
  Vertexff v0_;
  Vertexff v1_;
  Vertexff v2_;
  std::shared_ptr<Material> material_{};

  // Helper structs
  math::Vector3f triangle_plane_normal_{};
  float normal_sign_{1};
};

} // graphics::raytracer
