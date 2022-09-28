#ifndef OBJ_HPP
#define OBJ_HPP

#include <stdio.h>
#include <memory>
#include <array>
#include <vector>

namespace CPPML {

bool LoadOBJFile(FILE *file, std::vector<float>& retPositions, std::vector<float>& retTextureCoordinates, std::vector<float>& retNormals, std::vector<unsigned int>& retIndices);

/* Must export: Triangles, Vertices, Texcoords, and Normals */
bool LoadOBJFileOLD1(FILE *file, std::unique_ptr<float[]>& ret_vertices, std::unique_ptr<float[]>& ret_texcoords, std::unique_ptr<float[]>& ret_normals, unsigned int& vertexCount);

}

#endif