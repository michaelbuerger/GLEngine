# Contributors Read This!
---
## Some Useful Tools

### Installing valgrind (not required)

- **Ubuntu/Debian**: `sudo apt install valgrind`
- **macOS**: Install [homebrew](https://brew.sh/) then run`brew install valgrind`
---
## Testing Your Code

**The following commands can be run from a terminal in the project directory**:

!!! tip
    When adding new cpp files to the engine, re-running ```make make-project``` is required for them to be added to the CMake project (as it automatically finds all CPP files in the project).

- `make all` or `make`: Says what each make function does
- `make make-project`: Builds necessary dependencies with CMake  
- `make build-project`: Builds the engine
- `make execute-project`: Executes main.cpp
- `make build-execute project`: Runs `build-project` then `execute-project`
- `make qea`: Runs `make-project` then `build-project` then `execute-project`  
- `make line-count`: Queries line counts of various parts of the engine's code
- `make clean`: Runs all of the following clean commands
- `make clean-bin`: Clears bin directory of engine (not including sub-directories)

!!! tip
    Running ```make qea``` is a fast way to run all of the necessary make commands when testing your code.

---
## GitHub pipeline

!!! note
    GLEngine is currently in a chaotic stage of development, so contributing by formal means is difficult. If you are interested in contributing, or have any ideas, please reach out to me! Once the project reaches a stable stage, the pipeline will change drastically.

**Currently:**  
The [transfer1 branch](https://github.com/popwser/GLEngine/blob/transfer1) is the first place all changes end up, commits are frequent and chaotic. The other two branches are currently ignored.  
  
**When the project reaches a more stable stage:**  
The [develop branch](https://github.com/popwser/GLEngine/blob/develop) and the [release branch](https://github.com/popwser/GLEngine/blob/release) will not except commits directly, and will only be mutable through pull requests. To make changes, a new branch with **one of two** prefixes will be created:  
```issue-```  
```feature-```  
Once a feature or issue branch is ready to be merged, it will be rebased upon the **develop branch** and then a pull request will be created from the feature or issue branch into the **develop branch**.  
The **release branch** will only recieve pull requests when major milestones are reached. For me, this means when the project is in a good place in terms of functionality. 
---
## Useful Tidbits

!!! note 
    [**main.cpp**](https://github.com/popwser/GLEngine/blob/transfer1/src/main.cpp) is only for testing purposes and is not built into the static library.  