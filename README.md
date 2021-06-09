This is an [emscripten](https://emscripten.org/) project. At the moment, is really just a triangle rendered with OpenGL. However, you can already use it as an starting point for a Native and WASM OpenGL project, as cool thing is that it runs on both Native (OSX, Linux) and Web (WebAssembly) with the help of emscripten tooling.

### Building

To build it yourself, you first have to clone the projects with the submodules which are the libraries needed (glew and glfw).

```
git clone --recurse-submodules -j8 https://github.com/zant/woxel
cd woxel
```

### Native

**Requirements**

- [cmake](https://cmake.org/)
- [OpenGL](https://www.opengl.org/)

After you make sure you have all the requirements covered, run:

```
sh build.sh
```

### Web

**Requirements**

- All of the above
- [emscripten](https://emscripten.org/docs/getting_started/downloads.html)
- [python](https://www.python.org/downloads/)

Python is only really required for the HTTP server, you can serve the `embuild` folder as you will. After you make sure you have all the requirements covered, run:

```
sh embuild.sh
```
