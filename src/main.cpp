#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Renderer.h"
#include "Shader.h"
#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define GLFW_INCLUDE_ES3
#endif

GLFWwindow *window;

static void errorCallback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void forceExit() {
#ifdef __EMSCRIPTEN__
  emscripten_force_exit(EXIT_FAILURE);
#else
  exit(EXIT_FAILURE);
#endif
}

#ifdef __EMSCRIPTEN__
const char *vertexShaderSource = "attribute vec3 c;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(c, 1.0);\n"
                                 "}\0";
#else
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
#endif

#ifdef __EMSCRIPTEN__
const char *fragmentShaderSource =
    "void main()\n"
    "{\n"
    "   gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\n\0";
#else
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
#endif

static void generateFrame() {
  glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

int main() {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    printf("GLFW failer");
    forceExit();
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  window = glfwCreateWindow(480, 480, "Woxel", NULL, NULL);
  if (!window) {
    glfwTerminate();
    forceExit();
  }

  glfwSetKeyCallback(window, keyCallback);
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    forceExit();

  int vertexShader = Shader::loadShader("../res/shaders/Main.vert");
  int fragmentShader = Shader::loadShader("../res/shaders/Main.frag");

  int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glUseProgram(shaderProgram);

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(generateFrame, 0, false);
#else
  while (!glfwWindowShouldClose(window)) {
    generateFrame();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
#endif
}