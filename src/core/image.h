/*
Basic image class that writes to PPMs.

The image class is basically just a wrapper around some color buffer.
*/
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "color.h"

namespace {

constexpr std::string_view kEncoding = "P3";
constexpr int kMaxPpmValue = 255;

} // namespace

namespace graphics {

class Image {

public:
  explicit Image(size_t height, size_t width) : height_{height}, width_{width}, buffer_(height_, std::vector<Color>(width_)) {}

  Image(std::vector<std::vector<Color>> buffer) : height_{buffer.size()}, width_{buffer[0].size()}, buffer_(buffer) {}

  // Write out an image to |filepath|
  void write(const std::string& filepath) {
    std::ofstream file(filepath, std::ios::binary);

    // Set up PPM header component.
    file << kEncoding << '\n' << width_ << ' ' << height_ << '\n' << kMaxPpmValue << '\n';

    /*
    Actually write out the buffer elements to the image file. Note that these should be written
    out in a [0-255] range.
    */
    for (const auto& row : buffer_) {
      for (const auto& color : row) {
        // Normalize the color from [0.0 - 1.0] range to [0 - 255] range to print in the PPM.
        const auto max_color = std::max(1.f, std::max(color.r, std::max(color.g, color.b)));
        file << static_cast<int>(kMaxPpmValue * color.r / max_color) << ' '
          << static_cast<int>(kMaxPpmValue * color.g / max_color) << ' '
          << static_cast<int>(kMaxPpmValue * color.b / max_color) << '\t';
      }
      file << '\n';
    }
  }

  std::vector<Color>& operator[](const int i) {
    assert(i < height_);
    return buffer_[i];
  }

  // Set a pixel at an x, y cartesian coordinate.
  void set_pixel(Color c, size_t x, size_t y) {
    buffer_[height_ - y - 1][x] = c;
  }

  // Get a pixel at an x, y cartesian coordinate.
  Color& get_pixel(size_t x, size_t y) {
    return buffer_[height_ - y - 1][x];
  }

  constexpr size_t width() const {
    return width_;
  }

  constexpr size_t height() const {
    return height_;
  }

private:
  size_t height_;
  size_t width_;
  std::vector<std::vector<Color>> buffer_;
};

} // graphics
