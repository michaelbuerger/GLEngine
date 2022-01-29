all:
	@echo "make make-project          | Makes CMake files"
	@echo "make build-project         | Recompiles and links code"
	@echo "make line-count            | Runs cloc on CPPModelLibrary code"
	@echo "make line-count-all        | Runs cloc on all files in the local directory, including any extra downloaded files and resources"

make-project: # Sets up cmake files
	cmake -H. -Bbuild

build-project: # Builds project using setup cmake files
	cmake --build build -- -j3

qea:
	make make-project
	make build-project
	./build/test/Test

line-count:
	@echo "Getting line count of all project files (no 3rd party libraries etc.)..."
	cloc src/ include/ CMakeLists.txt makefile README.md .gitignore LICENSE

line-count-all:
	@echo "Getting line count of all files, including 3rd party libraries..."
	cloc .
