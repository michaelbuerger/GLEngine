add_executable(CPPML_Test test.cpp)
target_link_libraries(CPPML_Test PRIVATE CPPModelLibrary)
target_include_directories(CPPML_Test PRIVATE ../include/ ../spdlog-1.9.2/include/)
