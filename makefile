all:
	@echo "See documentation for options."

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

clean:
	make clean-bin

clean-bin:
	rm -rf bin/*
