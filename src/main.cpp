#include <iostream>
#include <string>

#include "math/vec.h"
#include "utils/image.h"

int main() {
  constexpr graphics::math::Vector3f v1{1., 3., 5.};
  constexpr graphics::math::Vector3f v2{1., 3., 5.};

  const int height = 100;
  const int width = 100;
  graphics::Image image{height, width};

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image.set_pixel(graphics::Color3f{1.0, 0.55, 0.3}, i, j);
    }
  }

  image.write("./test.ppm");

  return 0;
}
