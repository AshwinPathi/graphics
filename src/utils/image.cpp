#include <fstream>
#include <string_view>
#include <iostream>

#include "../utils/image.h"
#include "../utils/color.h"

namespace {

constexpr std::string_view kEncoding = "P3";
constexpr int kMaxPpmValue = 255;

} // namespace

namespace graphics {

Image::Image(size_t height, size_t width) : height_{height}, width_{width}, buffer_{height_ * width_} {}

void Image::write(std::string_view filepath) const {
  std::ofstream file(filepath, std::ios::binary);

  // Set up PPM header component.
  file << kEncoding << '\n' << width_ << ' ' << height_ << '\n' << kMaxPpmValue << '\n';

  // Write out all the PPM rows. Pretty print it for easier debugging, though this doesn't
  // actually matter for the actual format.
  for (size_t r = 0; r < height_; r++) {
    // std::clog << "\rScanlines remaining: " << (height_ - r) << ' ' << std::flush;
    for (size_t c = 0; c < width_; c++) {
      const auto& pixel =  get_pixel(r, c);
      file << pixel.r << ' ' << pixel.g << ' ' << pixel.b << '\t';
    }
    file << '\n';
  }
  // std::clog << "\rDone.                 \n";
}

void Image::set_pixel(const Color3& color, size_t r, size_t c) {
  buffer_[height_ * r + c] = color;
}

void Image::set_pixel(const Color3f& color, size_t r, size_t c) {
  set_pixel(to_color3(color), r, c);
}

Color3 Image::get_pixel(size_t r, size_t c) const {
  return buffer_[height_ * r + c];
}

Color3& Image::get_pixel(size_t r, size_t c) {
  return buffer_[height_ * r + c];
}

} // namespace graphics