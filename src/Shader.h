#pragma once

#include <string>

class Shader {
private:
  unsigned int m_ProgramID;

public:
  Shader(int vertexShader, int fragmentShader);
  ~Shader(){};
  void bind() const;
  void unbind() const;
  static GLuint loadShader(std::string file);
};