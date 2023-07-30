#include "src/core/color.h"
#include "src/core/ppm_image.h"


int main() {
    constexpr size_t height = 100;
    constexpr size_t width = 200;
    graphics::PPMImage image(height, width);
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            image[h][w] = graphics::RED;
        }
    }
    image.Write("test.ppm");
    return 0;
}
