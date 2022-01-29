# CPPModelLibrary

###### Ideals: Fast, Cross-Platform, Easy to use with OpenGL and Direct3D.

###### Please note that my main priority is to create a minimum viable product for use with [GLEngine](https://github.com/popwser/GLEngine).

**All documentation is being moved over to [GitHub Pages](https://popwser.github.io/CPPModelLibrary)**  
GitHub Pages Build Status:  
[![Build Status](https://travis-ci.org/popwser/CPPModelLibrary.svg?branch=develop)](https://travis-ci.org/popwser/CPPModelLibrary)

### Notes:

CPP Version: 17  
Uses libraries:

- spdlog (included, required)
- cloc (not included, not required)

## Including In Your Own Project (with CMake)

TODO
The static library is located in the **build** directory when the project is built.

## Getting Started

TODO

## Model formats to support reading from and writing to (likely in this order):

#### Priority:

- ASCII OBJ
- STL
- Collada
- FBX
- 3DS

#### Later:

- IGES
- STEP
- VRML/X3D

## makefile usage (for contributors)

**The following commands can be run from a terminal in the project directory**:

- `make all` or `make`: Says what each make function does
- `make make-project`: Builds necessary dependencies with CMake
- `make build-project`: Builds the library
- `make line-count`: Queries line counts of various parts of the library's code

## Links:

**Trello:** [https://trello.com/b/bgSspJZA/cppmodellibrary](https://trello.com/b/bgSspJZA/cppmodellibrary "Hi there :)")  
**GitHub:** [https://github.com/popwser/CPPModelLibrary](https://github.com/popwser/CPPModelLibrary "How are you today")
