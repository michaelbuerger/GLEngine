add_executable(GLEngine_Test src/main.cpp)
target_link_libraries(GLEngine_Test PRIVATE GLEngine ${PROJECT_SOURCE_DIR}/build/CPPModelLibrary/src/libCPPModelLibrary.a)
target_include_directories (GLEngine_Test PRIVATE
../include/
../spdlog-1.9.2/include/
../glew-2.1.0/include/
../glfw/include/
../CPPModelLibrary/include/
../include/imgui/
)