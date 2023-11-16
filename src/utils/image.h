/* PPM Image class. */
#pragma once

#include <vector>
#include <string_view>

#include "../utils/color.h"

namespace graphics {

// Implements a basic PPM image.
class Image {

public:
  Image(size_t height, size_t width);

  // Default move, copy, and dtor should suffice.

  void write(std::string_view filepath) const;

  void set_pixel(const Color3& color, size_t r, size_t c);

  void set_pixel(const Color3f& color, size_t r, size_t c);

  Color3 get_pixel(size_t r, size_t c) const;

  Color3& get_pixel(size_t r, size_t c);

  constexpr size_t width() const { return width_; }

  constexpr size_t height() const { return height_; }

private:
  size_t height_{};
  size_t width_{};

  // 1-d buffer. The buffer color should be between 0 and 255.
  std::vector<Color3> buffer_{};
};

} // namespace graphics
