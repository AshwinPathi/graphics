// Defines a list of objects that are intersectable. Acts as a wrapper for multiple
// intersectable objects in the world, and only implements one intersect method that
// returns the distance of the closest object intersected in its list.
#pragma once

#include <optional>
#include <vector>

#include "../../objects/intersectables/intersectable.h"
#include "../../utils/ray.h"

namespace graphics::raytracer {

class IntersectableList : public Intersectable {

public:
  IntersectableList() = default;

  IntersectableList(std::shared_ptr<Intersectable> intersectable) {
    AddObject(intersectable);
  }

  IntersectableList(std::vector<std::shared_ptr<Intersectable>> intersectable_list) {
    for (const auto& intersectable_obj : intersectable_list) {
      AddObject(intersectable_obj);
    }
  }

  void AddObject(std::shared_ptr<Intersectable> intersectable) {
    intersectable_list_.push_back(intersectable);
  }

  std::optional<ObjectIntersectionInfo> Intersect(const Ray& ray) const override {
    bool hit = false;
    float max_distance = std::numeric_limits<float>::max();

    ObjectIntersectionInfo intersection_info;

    for (const auto& intersectable : intersectable_list_) {
      if (auto intersection_record = intersectable->Intersect(ray)) {
        hit = true;
        if (intersection_record->t <= max_distance) {
          intersection_info = *intersection_record;
          max_distance = intersection_record->t;
        }
      }
    }

    //           Template type argument deduction
    return hit ? std::make_optional(intersection_info) : std::nullopt;
  }

public:
  std::vector<std::shared_ptr<Intersectable>> intersectable_list_{};
};

} // graphics::raytracer
