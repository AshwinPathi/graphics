#include "src/core/ppm_image.h"

#include <fstream>

namespace {

constexpr std::string_view kEncoding = "P3";
constexpr int kMaxPpmValue = 255;

} // namespace

namespace graphics {

PPMImage::PPMImage(size_t height, size_t width) : height_(height), width_(width), buffer_(height_, std::vector<Color>(width_)) {}

void PPMImage::Write(const std::string& path) {
  std::ofstream file(path, std::ios::binary);

  // Set up PPM header component.
  file << kEncoding << '\n' << width_ << ' ' << height_ << '\n' << kMaxPpmValue << '\n';

  // Write pixels per row.
  for (const auto& row : buffer_) {
    for (const auto& pixel : row) {
      // Normalize the color from [0.0 - 1.0] range to [0 - 255] range to print in the PPM.
      const auto max_color = std::max(1.f, std::max(pixel.r, std::max(pixel.g, pixel.b)));
      file << static_cast<int>(kMaxPpmValue * pixel.r / max_color) << ' '
        << static_cast<int>(kMaxPpmValue * pixel.g / max_color) << ' '
        << static_cast<int>(kMaxPpmValue * pixel.b / max_color) << '\t';
    }
    file << '\n';
  }
}

void PPMImage::SetPixel(Color c, size_t x, size_t y) {
  buffer_[height_ - y - 1][x] = c;
}

Color PPMImage::GetPixel(size_t x, size_t y) {
  return buffer_[height_ - y - 1][x];
}

} // graphics
