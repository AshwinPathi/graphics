// Parses scenes from file formats specified in: https://www.cs.virginia.edu/luther/4810/F2021/hw3.html

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#include "../objects/all_objects.h"
#include "../renderer/scene.h"
#include "../materials/all_materials.h"

namespace {

constexpr std::string_view kPngCommand = "png";
constexpr std::string_view kColorCommand = "color";
constexpr std::string_view kSphereCommand = "sphere";
constexpr std::string_view kPlaneCommand = "plane";
constexpr std::string_view kVertexCommand = "xyz";
constexpr std::string_view kTriangleCommand = "trif";
constexpr std::string_view kSunCommand = "sun";
constexpr std::string_view kBulbCommand = "bulb";

// for obj files
constexpr std::string_view kObjVertexCommand = "v";
constexpr std::string_view kObjTriangleCommand = "f";

}

namespace {

std::vector<std::string> SplitString(const std::string& s) {
  std::vector<std::string> split;
  std::istringstream iss(s);
  for(std::string line; std::getline(iss, line, ' '); ) {
    std::string stripped_line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");
    if (!stripped_line.empty() && stripped_line[0] != ' ') {
      split.push_back(stripped_line);
    }
  }
  return split;
}

} // namespace

namespace graphics::raytracer {

class SceneParser {
public:
  SceneParser() = default;

  Scene ReadScene(std::string_view path) {
    Scene scene {
      .objects = std::make_shared<IntersectableList>(),
      .background_color = graphics::Color3f{0.5, 0.7, 1.0} // Sky blue
    };

    std::string line;
    std::ifstream file(path);
    if (!file.is_open()) {
      std::cerr << "Unable to open file.\n";
    }
    while (std::getline(file, line)) {
      if (line == "\n" || line.empty() || line[0] == '#') {
        continue;
      }
      parseCommand(scene, SplitString(line));
    }
    file.close();
    std::cout << "Scene parsing complete.\n";
    return scene;
  }

private:
  void parseCommand(Scene& scene, const std::vector<std::string>& split_line) {
    if (split_line[0] == kPngCommand) {
      return;
    } else if (split_line[0] == kColorCommand) {
      updateColor(split_line);
    } else if (split_line[0] == kVertexCommand || split_line[0] == kObjVertexCommand) {
      addVertex(split_line);
    } else if (split_line[0] == kSphereCommand) {
      addSphere(scene, split_line);
    } else if (split_line[0] == kPlaneCommand) {
      addPlane(scene, split_line);
    } else if (split_line[0] == kTriangleCommand || split_line[0] == kObjTriangleCommand) {
      addTriangle(scene, split_line);
    } else if (split_line[0] == kSunCommand) {
      addSun(scene, split_line);
    } else if (split_line[0] == kBulbCommand) {
      addBulb(scene, split_line);
    } else {
      std::cerr << "Unsupported command: '" << split_line[0] << "' \n";
    }
  }

  void updateColor(const std::vector<std::string>& split_line) {
    current_color_ = Color3f {
      std::stof(split_line[1]),
      std::stof(split_line[2]),
      std::stof(split_line[3]),
    };
  }

  void addVertex(const std::vector<std::string>& split_line) {
    vertices_.push_back(math::Point3f{std::stof(split_line[1]), std::stof(split_line[2]), std::stof(split_line[3])});
  }

  void addSphere(Scene& scene, const std::vector<std::string>& split_line) const {
    auto diffuse_color = std::make_shared<Diffuse>(current_color_);
    auto center = math::Point3f {
      std::stof(split_line[1]),
      std::stof(split_line[2]),
      std::stof(split_line[3]),
    };
    float radius = std::stof(split_line[4]);
    auto sphere = std::make_shared<Sphere>(center, radius, diffuse_color);
    scene.objects->AddObject(sphere);
  }

  void addPlane(Scene& scene, const std::vector<std::string>& split_line) const {
    auto diffuse_color = std::make_shared<Diffuse>(current_color_);
    float A = std::stof(split_line[1]);
    float B = std::stof(split_line[2]);
    float C = std::stof(split_line[3]);
    float D = std::stof(split_line[4]);
    auto plane = std::make_shared<Plane>(A, B, C, D, diffuse_color);
    scene.objects->AddObject(plane);
  }

  void addTriangle(Scene& scene, const std::vector<std::string>& split_line) const {
    auto diffuse_color = std::make_shared<Diffuse>(current_color_);
    auto v1 = getVertex(std::stoi(split_line[1]));
    auto v2 = getVertex(std::stoi(split_line[2]));
    auto v3 = getVertex(std::stoi(split_line[3]));
    auto triangle = std::make_shared<Triangle>(v1, v2, v3, diffuse_color);
    scene.objects->AddObject(triangle);
  }

  void addSun(Scene& scene, const std::vector<std::string>& split_line) const {
    auto sun = std::make_shared<Sun>(
      math::Point3f{
        std::stof(split_line[1]),
        std::stof(split_line[2]),
        std::stof(split_line[3])
      },
      current_color_
    );
    scene.lights.push_back(sun);
  }

  void addBulb(Scene& scene, const std::vector<std::string>& split_line) const {
    auto bulb = std::make_shared<Bulb>(
      math::Point3f{
        std::stof(split_line[1]),
        std::stof(split_line[2]),
        std::stof(split_line[3])
      },
      current_color_
    );
    scene.lights.push_back(bulb);
  }

  inline math::Point3f getVertex(int i) const {
    if (i < 0) {
      return vertices_[vertices_.size() + i];
    }
    return vertices_[i - 1];
  }

  std::vector<math::Point3f> vertices_{};
  Color3f current_color_{colors::White};
};

} // namespace graphics::raytracer
