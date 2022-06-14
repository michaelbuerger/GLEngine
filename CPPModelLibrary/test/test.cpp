/* Remember! Test has to be either empty or error-less before committing. Even when transferring between computers. */

#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>

#include "CPPML/logging/logging.hpp"
#include "CPPML/loading/loading.hpp"
#include "CPPML/loading/OBJ.hpp"

using namespace CPPML;

int main() {
   CPPML::Log::Init(true); // true turns debug log on, false turns debug log off
   // CPPML::Log::Init(spdlog::level::warn); // alternatively, the logger can be set to only display a certain level or above

   // UNIX filepath
   std::string filepath = "test/models/cube.obj";
   
#ifdef _WIN32 // WINDOWS filepath, specific dependent on my system, can change
   filepath = "C:\\Users\\Michael Buerger\\Documents\\GitHub\\CPPModelLibrary\\test\\models\\cube.obj";
#endif

   FILE* modelFile = OpenFile(filepath.c_str());

   std::vector<float> positions;
   std::vector<float> textureCoords;
   std::vector<float> normals;
   std::vector<unsigned int> indices;

   bool success = LoadOBJFile(modelFile, positions, textureCoords, normals, indices);

   if(!success)
   {
      CPPML_ERROR("Loading OBJ File Unsuccessful");
   }

   for(unsigned int i=0; i < positions.size(); i++) {
      CPPML_INFO("v {}", positions[i]);
   }

   for(unsigned int i=0; i < textureCoords.size(); i++) {
      CPPML_INFO("vt {}", textureCoords[i]);
   }

   for(unsigned int i=0;i < normals.size(); i++) {
      CPPML_INFO("vn {}", normals[i]);
   }

   for(unsigned int i=0; i < indices.size(); i++) {
      CPPML_INFO("i {}", indices[i]);
   }

   return 0;
}
