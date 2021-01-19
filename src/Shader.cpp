#include <iostream>

#include "Renderer.h"
#include "Shader.h"
#include "System.h"

void Shader::bind() const { glUseProgram(m_RendererID); }

void Shader::loadShader(std::string file) {
  GLuint shader;

  std::string source = System::readFile(file);
  std::string extension = System::extension(file);

  if (extension == "vert") {
    shader = glCreateShader(GL_VERTEX_SHADER);
  } else if (extension == "frag") {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  }

  glShaderSource(shader, 1, (char **)&source, NULL);
  glCompileShader(shader);

  int success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "Shader compulation failed\n" << infoLog << std::endl;
  }
}