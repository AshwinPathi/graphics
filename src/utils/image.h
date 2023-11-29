// PPM Image class.
#pragma once

#include <fstream>
#include <iostream>
#include <array>
#include <string_view>

#include "../utils/color.h"

namespace {

constexpr std::string_view kEncoding = "P3";
constexpr int kMaxPpmValue = 255;

} // namespace

namespace graphics {

// Implements a basic PPM image. Accesses to the image class should be done through set/get pixel,
// since these transparently convert Colors between Color3f and Color3, and they access the buffer
// with the correct offsets.
class Image {

public:
  Image(size_t height, size_t width) : height_{height}, width_{width}, buffer_{height_ * width_} {}

  void write(std::string_view filepath) const {
    std::ofstream file(filepath, std::ios::binary);

    // Set up PPM header component.
    file << kEncoding << '\n' << width_ << ' ' << height_ << '\n' << kMaxPpmValue << '\n';

    // Write out all the PPM rows. Pretty print it for easier debugging, though this doesn't
    // actually matter for the actual format.
    for (size_t r = 0; r < height_; r++) {
      for (size_t c = 0; c < width_; c++) {
        const auto& pixel =  get_pixel(r, c);
        file << pixel.r << ' ' << pixel.g << ' ' << pixel.b << '\t';
      }
      file << '\n';
    }
  }

  constexpr void set_pixel(const Color3& color, size_t r, size_t c) {
    buffer_[to_1d(r, c)] = color;
  }

  constexpr void set_pixel(const Color3f& color, size_t r, size_t c) {
    set_pixel(to_color3(color), r, c);
  }

  constexpr Color3 get_pixel(size_t r, size_t c) const {
    return buffer_[to_1d(r, c)];
  }

  constexpr Color3& get_pixel(size_t r, size_t c) {
    return buffer_[to_1d(r, c)];
  }

  constexpr size_t width() const { return width_; }

  constexpr size_t height() const { return height_; }

  constexpr const Color3& operator[](int i) const {
    return buffer_[i];
  }

  constexpr Color3& operator[](int i) {
    return buffer_[i];
  }

private:

  int to_1d(int r, int c) const {
    return width_ * r + c;
  }

  size_t height_{};
  size_t width_{};

  // 1-d buffer. The buffer color is a triple of values, where each value is between 0 and 255.
  std::vector<Color3> buffer_{};
};

} // namespace graphics
