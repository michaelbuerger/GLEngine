# GLEngine  
---
## About
GLEngine is a complete game engine developed by Michael Buerger
Using the following libraries:

- [glfw](https://www.glfw.org) (Windows, Input Handling, etc)
- [glew](http://glew.sourceforge.net) (OpenGL Extension Wrangler)
- [glm](https://glm.g-truc.net/0.9.9/index.html) (OpenGL Mathematics)
- [spdlog](https://github.com/gabime/spdlog) (Fast C++ logging, fancy colored text in console, easy formatting)
- [stb_image.h](https://github.com/nothings/stb) (Single-file image loader)
- [CPPModelLibrary](https://github.com/popwser/CPPModelLibrary) (CPP library for loading model files)
---
## Installation

#### If you are **not** contributing
Grab the latest version of GLEngine [here](https://github.com/popwser/GLEngine/archive/transfer1.zip). This will download the repository in ZIP form, which automatically excludes unnecessary files.

#### If you are contributing
Clone the latest version of GLEngine  
```
git clone https://github.com/popwser/GLEngine.git
```
and see [the contributing page.](contributing/)

From there, download and install **glew** (instructions below).

All libraries/binaries used within the engine are self-contained in the repository except for the following:

- glew (**required**)

#### Installing glew-2.1.0 (required)

1. Go to the [GLEW Sourceforge](http://glew.sourceforge.net/) page.
2. Find the download for version [2.1.0](https://sourceforge.net/projects/glew/files/glew/2.1.0/).
3. Download the applicable file (win32.zip, zip, or tgz).
4. Take the contained glew-2.1.0 folder and move it into the project directory.
5. Within a terminal run: `make make-project` to build the necessary dependencies with CMake.
---
## Links

**Read the docs!** <https://glengine.readthedocs.org/en/latest/>  
**Trello**: <https://trello.com/b/Pl9kCp8s/glengine>  
**GitHub**: <https://github.com/popwser/GLEngine>
