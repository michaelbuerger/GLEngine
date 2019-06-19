# GLEngine
A complete game engine developed by Michael Buerger
Using the following libraries:
- glfw (Windows, Input Handling, etc)
- glew (OpenGL Extension Wrangler)
- glm (OpenGL Mathematics)
- spdlog (Mainly for console colors)

## Installation
All libraries/binaries used within the engine are self-contained in the repository except for the following:
- glew (required)
- cloc (not required)

#### Installing glew-2.1.0:
1. Go to the [GLEW Sourceforge](http://glew.sourceforge.net/) page.
2. Find the download for version [2.1.0](https://sourceforge.net/projects/glew/files/glew/2.1.0/).
3. Download the applicable file (win32.zip, zip, or tgz).
4. Take the contained glew-2.1.0 folder and move it into the project directory.
5. Within a terminal run: ```make make-project``` to build the necessary dependencies with CMake.

#### Installing cloc:
- **Ubuntu/Debian**: ```sudo apt install cloc```
- **macOS**: Install **homebrew** then run```brew install cloc```


## Running
**The following commands can be run from a terminal in the project directory**:

- ```make all``` or ```make```: Says what each make function does
- ```make make-project```: Builds necessary dependencies with CMake
- ```make build-project```: Builds the engine
- ```make execute-project```: Executes main.cpp
- ```make build-execute project```: Runs ```build-project``` then ```execute-project```
- ```make qea```: Runs ```make-project``` then ```build-project``` then ```execute-project```
- ```make line-count```: Queries line counts of various parts of the engine's code
- ```make clean```: Runs all of the following clean commands
- ```make clean-bin```: Clears bin directory of engine (not including sub-directories)

**Developer's Note:**

When adding new cpp files to the engine, re-running ```make-project``` is required for them to be built.

## Links
**Trello**: <https://trello.com/b/Pl9kCp8s/glengine>  
**GitHub**: <https://github.com/popwser/GLEngine>
