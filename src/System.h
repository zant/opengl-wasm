#pragma once

#include <string>

class System {
public:
  static std::string readFile(std::string file);
  static std::string extension(std::string filename);
};