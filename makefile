all:
	@echo "make make-project          | Makes CMake files"
	@echo "make build-project         | Recompiles and links code"
	@echo "make execute-project       | Runs binary in bin directory"
	@echo "make build-execute-project | Runs build and execute"
	@echo "make qea                   | Quick Easy All: Run make, build, then execute"
	@echo "make line-count            | Runs cloc on GLEngine code"
	@echo "make line-count-all        | Runs cloc on all files in the local directory, including any extra downloaded files and resources"
	@echo "make clean                 | Runs all clean commands like: 'clean-*'"
	@echo "make clean-bin             | Clears binary directory"

build-execute-project:
	make build-project
	make execute-project

make-project: # Sets up cmake files
	cmake -H. -Bbuild

build-project: # Builds project using setup cmake files
	cmake --build build -- -j3

execute-project: # Run generated executable
	@echo "----PROGRAM OUTPUT----"
	@bin/GLEngine
	@echo "----------------------"

qea:
	make make-project
	make build-execute-project

line-count:
	@echo "Getting line count of all project files, excluding including 3rd party libraries..."
	cloc src/GLEngine/ include/GLEngine/ examples/ doc/ CMakeLists.txt makefile README.md .gitignore

line-count-all:
	@echo "Getting line count of all files, including 3rd party libraries..."
	cloc .

clean:
	make clean-bin

clean-bin:
	rm -rf bin/*
