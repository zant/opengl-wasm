#include "System.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = std::__fs::filesystem;

std::string System::extension(std::string filename) {
  return filename.substr(filename.find_last_of(".") + 1);
}

std::string System::readFile(std::string file) {
  std::ifstream stream(file);
  std::stringstream sstr;
  sstr << stream.rdbuf();
  return sstr.str();
}