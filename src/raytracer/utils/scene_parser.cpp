/*
Parses scenes from file formats specified in: https://www.cs.virginia.edu/luther/4810/F2021/hw3.html
*/
#include "src/raytracer/utils/scene_parser.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "src/raytracer/renderer/renderer_utils.h"
#include "src/raytracer/renderer/world.h"
#include "src/raytracer/shapes/intersectable.h"
#include "src/raytracer/shapes/sphere.h"
#include "src/raytracer/shapes/plane.h"

namespace {

constexpr std::string_view kPngCommand = "png";
constexpr std::string_view kColorCommand = "color";
constexpr std::string_view kSphereCommand = "sphere";
constexpr std::string_view kPlaneCommand = "plane";
constexpr std::string_view kSunCommand = "sun";

}

namespace graphics::raytracer {

std::vector<std::string> ReadFile(const std::string& path) {
  std::vector<std::string> file_tokens;

  std::string line;
  std::ifstream file(path);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      if (line == "\n" || line.empty()) {
        continue;
      }
      std::istringstream iss(line);
      std::string token;
      while (std::getline(iss, token, ' ')) {
        if (token.empty() || token == " " || token[0] == '#') { continue; }
        file_tokens.push_back(token);
      }
    }
    file.close();
  } else {
    std::cout << "Unable to open file.\n";
  }
  return file_tokens;
}

SceneInfo ReadScene(const std::string& path) {

  const std::vector<std::string>& file_tokens = ReadFile(path);
  const int N = file_tokens.size();

  World world;
  std::vector<PointLight> point_light_sources;

  Color current_color{1., 1., 1.};

  size_t height{};
  size_t width{};

  int iter = 0;
  while (iter < N) {
    const auto& token = file_tokens[iter++];
    if (token == kPngCommand) {
      // Parse png file stuff
      width = std::stoi(file_tokens[iter++]);
      height = std::stoi(file_tokens[iter++]);
      iter++;
    } else if (token == kSphereCommand) {
      Sphere sphere{
        math::Vector3{
          std::stof(file_tokens[iter++]),
          std::stof(file_tokens[iter++]),
          std::stof(file_tokens[iter++])
        },
        std::stof(file_tokens[iter++]),
        Material {
          current_color
        }
      };
      world.AddObject(std::make_shared<Sphere>(sphere));
    } else if (token == kPlaneCommand) {
      Plane plane{
        std::stof(file_tokens[iter++]),
        std::stof(file_tokens[iter++]),
        std::stof(file_tokens[iter++]),
        std::stof(file_tokens[iter++]),
        Material {
          current_color
        }
      };
      world.AddObject(std::make_shared<Plane>(plane));
    } else if (token == kSunCommand) {
      PointLight source {
          .color = current_color,
          .direction = {
            std::stof(file_tokens[iter++]),
            std::stof(file_tokens[iter++]),
            std::stof(file_tokens[iter++])
          }
      };
      point_light_sources.push_back(source);
    } else if (token == kColorCommand) {
      current_color = Color{
        std::stof(file_tokens[iter++]),
        std::stof(file_tokens[iter++]),
        std::stof(file_tokens[iter++])
      };
    }
  }

  // Construct the scene.
  SceneInfo scene {
    .height = height,
    .width = width,
    .world = std::move(world),
    .background_color = graphics::BLACK,
    .point_lights = std::move(point_light_sources)
  };

  return scene;
}

} // graphics
