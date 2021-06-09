# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (woxel)

file(GLOB ROOT_SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB ROOT_HEADER ${PROJECT_SOURCE_DIR}/src/*.h)

file(GLOB ROOT_SOURCE_VENDOR ${PROJECT_SOURCE_DIR}/src/vendor/**/*.cpp)
file(GLOB ROOT_HEADER_VENDOR ${PROJECT_SOURCE_DIR}/src/vendor/**/*.h)

# The main executable
add_executable(main ${ROOT_SOURCE} ${ROOT_HEADER} ${ROOT_SOURCE_VENDOR} ${ROOT_HEADER_VENDOR})

set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 
    set_target_properties(main
    PROPERTIES SUFFIX ".html"
    LINK_FLAGS "-Os -o index.html -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1 --preload-file res/shaders/Frag.web.hlsl --preload-file res/shaders/Vert.web.hlsl")
else()
  # glfw
  add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
  target_link_libraries(main PRIVATE glfw)

  # glew
  add_definitions(-DGLEW_STATIC)
  add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
  target_link_libraries(main PRIVATE libglew_static)
endif()
