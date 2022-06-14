file (GLOB_RECURSE source_files "./*.cpp")

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory (${PROJECT_SOURCE_DIR}/glfw/ ${PROJECT_SOURCE_DIR}/build/glfw/)
add_subdirectory (${PROJECT_SOURCE_DIR}/CPPModelLibrary/ ${PROJECT_SOURCE_DIR}/build/CPPModelLibrary/)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang") # linux
    add_subdirectory (${PROJECT_SOURCE_DIR}/glew-2.1.0/build/cmake/ ${PROJECT_SOURCE_DIR}/build/glew-2.1.0)
endif()

add_library (GLEngine STATIC ${source_files})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang") # linux
    target_link_libraries(GLEngine glew glfw)
else() # windows
    target_link_libraries(GLEngine ${PROJECT_SOURCE_DIR}/glew-2.1.0/lib/Debug/x64 glfw)
endif()
target_include_directories (GLEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/spdlog-1.9.2/include/
    ${PROJECT_SOURCE_DIR}/glew-2.1.0/include/
    ${PROJECT_SOURCE_DIR}/glfw/include/
    ${PROJECT_SOURCE_DIR}/CPPModelLibrary/include/
    ${PROJECT_SOURCE_DIR}/include/imgui/
)
