all:
	@echo "make make-project          | Makes CMake files"
	@echo "make build-project         | Recompiles and links code"
	@echo "make execute-project       | Runs binary in bin directory"
	@echo "make build-execute-project | Runs build and execute"
	@echo "make line-count            | Runs cloc on code written myself"
	@echo "make clean                 | Runs all clean commands like: 'clean-*'"
	@echo "make clean-bin             | Clears binary directory"

build-execute-project:
	make build-project
	clear
	make execute-project

make-project: # Sets up cmake files
	cmake -H. -Bbuild

build-project: # Builds project using setup cmake files
	cmake --build build -- -j3

execute-project: # Run generated executable
	bin/GLEngine

line-count:
	cloc src/ include/ spike/ doc/ CMakeLists.txt makefile README.md .gitignore

clean:
	make clean-bin

clean-bin:
	rm -rf bin/*
