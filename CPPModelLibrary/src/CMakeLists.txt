add_library (CPPModelLibrary STATIC useful.cpp loading/loading.cpp loading/OBJ.cpp logging/Log.cpp)
target_include_directories (CPPModelLibrary PRIVATE ../include/ ../spdlog-1.9.2/include/)
