all:
	@echo "make make-project          | Makes CMake files"
	@echo "make build-project         | Recompiles and links code"
	@echo "make execute-project       | Runs binary in bin directory"
	@echo "make build-execute-project | Runs build and execute"
	@echo "make qea                   | Quick Easy All: Run make, build, then execute"
	@echo "make line-count            | Runs cloc on GLEngine code"
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
	cloc src/ include/ spike/ doc/ CMakeLists.txt makefile README.md .gitignore

clean:
	make clean-bin

clean-bin:
	rm -rf bin/*
