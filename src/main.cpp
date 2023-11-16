#include <iostream>
#include <string>
#include <type_traits>

#include "math/vec.h"
#include "utils/image.h"

template <size_t height, size_t width>
constexpr graphics::Image<height, width> create_image() {
  graphics::Image<height, width> image;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      auto r = static_cast<float>(i) / (width-1);
      auto g = static_cast<float>(j) / (height-1);
      auto b = 0.f;
      image.set_pixel(graphics::Color3f{r, g, b}, i, j);
    }
  }

  return image;
}

int main() {
  constexpr graphics::math::Vector3f v1{1., 3., 5.};
  constexpr graphics::math::Vector3f v2{1., 3., 5.};
  constexpr graphics::math::Vector3f v3 = v1 + v2;

  constexpr size_t height = 100;
  constexpr size_t width = 100;
  constexpr auto image = create_image<height, width>();

  // This part is not constexpr but everything above is.
  image.write("./test.ppm");
  return 0;
}
