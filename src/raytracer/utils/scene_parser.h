/*
Parses scenes from file formats specified in: https://www.cs.virginia.edu/luther/4810/F2021/hw3.html
*/
#pragma once

#include <vector>
#include <string>

#include "src/raytracer/renderer/renderer_utils.h"

namespace graphics::raytracer {

// Read a scene from a given file path.
SceneInfo ReadScene(const std::string& path);

// Read lines of a file into a vector of strings.
std::vector<std::string> ReadFile(const std::string& path);


} // graphics
