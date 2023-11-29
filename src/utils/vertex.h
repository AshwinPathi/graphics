// Represents a vertex, which logically is a point (and potentially a normal).
#pragma once

#include <optional>

#include "../math/vec.h"
#include "../math/math_utils.h"

namespace graphics {

template <typename PointT, typename NormalT>
struct Vertex {
  math::Vector<PointT, 3> point{};
  std::optional<math::Vector<NormalT, 3>> normal{}; // We may or may not have a normal
};

using Vertexff = Vertex<float, float>;

} // namespace graphics
