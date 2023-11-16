#pragma once
#include <vector>
#include <tuple>
#include <string>

#include "src/core/color.h"

namespace graphics {

class PPMImage {

public:
  explicit PPMImage(size_t width, size_t height);

  void Write(const std::string& filepath);

  // Set a pixel at an x, y cartesian coordinate.
  void SetPixel(Color c, size_t x, size_t y);

  // Get a pixel at an x, y cartesian coordinate. Returns by value.
  Color GetPixel(size_t x, size_t y);


  std::vector<Color>& operator[](int i) {
    return buffer_[i];
  }

  constexpr size_t width() const {
    return width_;
  }

  constexpr size_t height() const {
    return height_;
  }

private:
  size_t width_{};
  size_t height_{};
  std::vector<std::vector<Color>> buffer_{};
};


} // graphics
