#include "CPPML/loading/OBJ.hpp"

#include "CPPML/logging/logging.hpp"
#include "CPPML/useful.hpp"

#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <unordered_map>
#include <string>

namespace CPPML
{

struct VertexPosition
{
    float x, y, z;
};

struct VertexTextureCoords
{
    float u, v;
};

struct VertexNormal
{
    float i, j, k;
};

struct IndexedFaceVertex
{
    uint vertexPositionIndex, vertexTextureCoordsIndex, vertexNormalIndex;

    // detect collision in unordered_map
    bool operator==(const IndexedFaceVertex& other) const
    {
        return vertexPositionIndex == other.vertexPositionIndex &&
        vertexTextureCoordsIndex == other.vertexTextureCoordsIndex &&
        vertexNormalIndex == other.vertexNormalIndex;
    }
};

template <class T>
inline void hash_combine(std::size_t & s, const T& v)
{
  std::hash<T> h;
  s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
}

struct hash_fn
{
    std::size_t operator() (const IndexedFaceVertex& indexedFaceVertex) const
    {
        std::size_t hres = 0;

        hash_combine(hres, indexedFaceVertex.vertexPositionIndex);
        hash_combine(hres, indexedFaceVertex.vertexTextureCoordsIndex);
        hash_combine(hres, indexedFaceVertex.vertexNormalIndex);
        return hres;
    }
};

bool LoadOBJFile(FILE *file, std::vector<float>& retPositions, std::vector<float>& retTextureCoordinates, std::vector<float>& retNormals, std::vector<uint>& retIndices)
{
    auto positionsPool = std::vector<VertexPosition>(); // contains all data specified by 'v'
    auto textureCoordinatesPool = std::vector<VertexTextureCoords>(); // contains all data specified by 'vt'
    auto normalsPool = std::vector<VertexNormal>(); // contains all data specified by 'vn'

    // for keeping track of duplicates + indicesIndex for faceVertices
    auto indexedFaceVerticesIndexMap = std::unordered_map<IndexedFaceVertex, uint, hash_fn>();
    uint currentIndicesIndex = 0;

    // FILE pointer invalid, file never opened or was closed before loading
    if(file == nullptr)
    {
        CPPML_ERROR("In method \"LoadOBJFile\". FILE pointer invalid: File never opened or was closed before loading.");
        return false;
    }

    // this is only used for outputting error/trace info
    int currentLine = 1;

    while(!feof(file))
    {
        /* Per line operations */

        // Note that if the first sequence of non-whitespace charactes in a line (first string) is too long, a segfault will occur
        char header[128]; 
        
        if(fscanf(file, "%s", header) == EOF)
        {
            CPPML_TRACE("In method \"LoadOBJFile\". Reached end-of-file while attempting to read header of line {}", currentLine);
            break;
        }

        if(!strcmp(header, "v"))
        {
            float x, y, z;
            if(fscanf(file, "%f %f %f\n", &x, &y, &z) == EOF)
            {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            positionsPool.push_back({ x, y, z });
        } else if(!strcmp(header, "vt"))
        {
            float u, v;
            if(fscanf(file, "%f %f\n", &u, &v) == EOF)
            {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            textureCoordinatesPool.push_back({ u, v });
        } else if(!strcmp(header, "vn"))
        {
            float i, j, k;
            if(fscanf(file, "%f %f %f\n", &i, &j, &k) == EOF)
            {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            normalsPool.push_back({ i, j, k });
        } else if(!strcmp(header, "f"))
        {
            IndexedFaceVertex indexedFaceVertex0, indexedFaceVertex1, indexedFaceVertex2;

            int res = fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n",
            &indexedFaceVertex0.vertexPositionIndex, &indexedFaceVertex0.vertexTextureCoordsIndex, &indexedFaceVertex0.vertexNormalIndex,
            &indexedFaceVertex1.vertexPositionIndex, &indexedFaceVertex1.vertexTextureCoordsIndex, &indexedFaceVertex1.vertexNormalIndex,
            &indexedFaceVertex2.vertexPositionIndex, &indexedFaceVertex2.vertexTextureCoordsIndex, &indexedFaceVertex2.vertexNormalIndex);

            // convert to zero based indexing
            indexedFaceVertex0.vertexPositionIndex--;
            indexedFaceVertex0.vertexTextureCoordsIndex--;
            indexedFaceVertex0.vertexNormalIndex--;

            indexedFaceVertex1.vertexPositionIndex--;
            indexedFaceVertex1.vertexTextureCoordsIndex--;
            indexedFaceVertex1.vertexNormalIndex--;

            indexedFaceVertex2.vertexPositionIndex--;
            indexedFaceVertex2.vertexTextureCoordsIndex--;
            indexedFaceVertex2.vertexNormalIndex--;

            if (res == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                CPPML_ERROR("Note: An EOF error can be produced if face specifications don't have the right structure, or are missing information (make sure your export settings are correct and include vertices, texture coordinates, and normals)");
                return false;
            }

            /* The following section assumes that any referenced attributes (in face specs) are previously specified */
            /* OBJ should specify in this way, if not, this code will have to be moved to another for loop at the end */

            // checks if indexedFaceVertex has been seen before (key only) and inserts if it hasn't (key + index)
            bool duplicate = !indexedFaceVerticesIndexMap.try_emplace(indexedFaceVertex0, currentIndicesIndex).second;
            if(duplicate) // indexedFaceVertex exists already
            {
                // no need to push_back any attribute information, only index of current face
                retIndices.push_back(indexedFaceVerticesIndexMap[indexedFaceVertex0]);
            } else  // indexFaceVertex is at end of vector
            {
                // positions, textureCoordinates, and normals must be pushed_back as their combo is unique (so far)
                retPositions.push_back(positionsPool[indexedFaceVertex0.vertexPositionIndex].x);
                retPositions.push_back(positionsPool[indexedFaceVertex0.vertexPositionIndex].y);
                retPositions.push_back(positionsPool[indexedFaceVertex0.vertexPositionIndex].z);

                retTextureCoordinates.push_back(textureCoordinatesPool[indexedFaceVertex0.vertexTextureCoordsIndex].u);
                retTextureCoordinates.push_back(textureCoordinatesPool[indexedFaceVertex0.vertexTextureCoordsIndex].v);

                retNormals.push_back(normalsPool[indexedFaceVertex0.vertexNormalIndex].i);
                retNormals.push_back(normalsPool[indexedFaceVertex0.vertexNormalIndex].j);
                retNormals.push_back(normalsPool[indexedFaceVertex0.vertexNormalIndex].k);

                retIndices.push_back(currentIndicesIndex);
                currentIndicesIndex++; // only increment if new (unique so far) faceVertex is found
            }

            // Same code for next indexedFaceVertex in trio
            // checks if indexedFaceVertex has been seen before (key only) and inserts if it hasn't (key + index)
            duplicate = !indexedFaceVerticesIndexMap.try_emplace(indexedFaceVertex1, currentIndicesIndex).second;
            if(duplicate) // indexedFaceVertex exists already
            {
                // no need to push_back any attribute information, only index of current face
                retIndices.push_back(indexedFaceVerticesIndexMap[indexedFaceVertex1]);
            } else // new indexedFaceVertex is at end of vector
            {
                // positions, textureCoordinates, and normals must be pushed_back as their combo is unique (so far)
                retPositions.push_back(positionsPool[indexedFaceVertex1.vertexPositionIndex].x);
                retPositions.push_back(positionsPool[indexedFaceVertex1.vertexPositionIndex].y);
                retPositions.push_back(positionsPool[indexedFaceVertex1.vertexPositionIndex].z);

                retTextureCoordinates.push_back(textureCoordinatesPool[indexedFaceVertex1.vertexTextureCoordsIndex].u);
                retTextureCoordinates.push_back(textureCoordinatesPool[indexedFaceVertex1.vertexTextureCoordsIndex].v);

                retNormals.push_back(normalsPool[indexedFaceVertex1.vertexNormalIndex].i);
                retNormals.push_back(normalsPool[indexedFaceVertex1.vertexNormalIndex].j);
                retNormals.push_back(normalsPool[indexedFaceVertex1.vertexNormalIndex].k);

                retIndices.push_back(currentIndicesIndex);
                currentIndicesIndex++; // only increment if new (unique so far) faceVertex is found
            }

            // Same code for next indexedFaceVertex in trio
            // checks if indexedFaceVertex has been seen before (key only) and inserts if it hasn't (key + index)
            duplicate = !indexedFaceVerticesIndexMap.try_emplace(indexedFaceVertex2, currentIndicesIndex).second;
            if(duplicate) // indexedFaceVertex exists already
            {
                // no need to push_back any attribute information, only index of current face
                retIndices.push_back(indexedFaceVerticesIndexMap[indexedFaceVertex2]);
            } else // new indexedFaceVertex is at end of vector
            {
                // positions, textureCoordinates, and normals must be pushed_back as their combo is unique (so far)
                retPositions.push_back(positionsPool[indexedFaceVertex2.vertexPositionIndex].x);
                retPositions.push_back(positionsPool[indexedFaceVertex2.vertexPositionIndex].y);
                retPositions.push_back(positionsPool[indexedFaceVertex2.vertexPositionIndex].z);

                retTextureCoordinates.push_back(textureCoordinatesPool[indexedFaceVertex2.vertexTextureCoordsIndex].u);
                retTextureCoordinates.push_back(textureCoordinatesPool[indexedFaceVertex2.vertexTextureCoordsIndex].v);

                retNormals.push_back(normalsPool[indexedFaceVertex2.vertexNormalIndex].i);
                retNormals.push_back(normalsPool[indexedFaceVertex2.vertexNormalIndex].j);
                retNormals.push_back(normalsPool[indexedFaceVertex2.vertexNormalIndex].k);

                retIndices.push_back(currentIndicesIndex);
                currentIndicesIndex++; // only increment if new (unique so far) faceVertex is found
            }
        } else
        {
            CPPML_TRACE("In method \"LoadOBJFile\". Line header of line {} was ignored: \"{}\"", currentLine, header);
            if(ScanTillNewline(file) == EOF)
            { // reads till new-line, effectively skips to next line
                break;
            }
        }
        currentLine++;
    }
    CPPML_TRACE("In method \"LoadOBJFile\". Reached EOF.");

    return true;
}

/* Must export: Triangles, Vertices, Texcoords, and Normals */
bool LoadOBJFileOLD1(FILE *file, std::unique_ptr<float[]>& ret_vertices, std::unique_ptr<float[]>& ret_texcoords, std::unique_ptr<float[]>& ret_normals, uint& vertexCount) {
    auto tempVertices = std::vector<std::array<float, 3>>();
    auto tempTexcoords = std::vector<std::array<float, 2>>();
    auto tempNormals = std::vector<std::array<float, 3>>();

    auto vertexIndices = std::vector<uint>();
    auto texcoordIndices = std::vector<uint>();
    auto normalIndices = std::vector<uint>();

    // Error handling related stuff
    int currentLine = 1;

    if(file == nullptr) { // FILE pointer invalid, file never opened or was closed before loading
        CPPML_ERROR("In method \"LoadOBJFile\". FILE pointer invalid: File never opened or was closed before loading.");
        return false;
    }

    while(!feof(file)) {
        // Per line operations
        char header[128]; 
        /* Note that if the first sequence of non-whitespace charactes in a line (first string) is too long
         * a segfault will occur
         */
        
        if(fscanf(file, "%s", header) == EOF) {
            CPPML_TRACE("In method \"LoadOBJFile\". Reached end-of-file while attempting to read header of line {}", currentLine);
            break;
        }

        if(!strcmp(header, "v")) {
            float x, y, z;
            if(fscanf(file, "%f %f %f\n", &x, &y, &z) == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            tempVertices.push_back({ x, y, z });
        } else if(!strcmp(header, "vt")) {
            float u, v;
            if(fscanf(file, "%f %f\n", &u, &v) == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            tempTexcoords.push_back({ u, v });
        } else if(!strcmp(header, "vn")) {
            float x, y, z;
            if(fscanf(file, "%f %f %f\n", &x, &y, &z) == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                return false;
            }

            tempNormals.push_back({ x, y, z });
        } else if(!strcmp(header, "f")) {
            uint vi0, ti0, ni0, vi1, ti1, ni1, vi2, ti2, ni2;
            int res = fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n", &vi0, &ti0, &ni0, &vi1, &ti1, &ni1, &vi2, &ti2, &ni2);
            if (res == EOF) {
                CPPML_ERROR("In method \"LoadOBJFile\". Reached end-of-file while attempting to read body of line {} with header \"{}\"", currentLine, header);
                CPPML_ERROR("Note: An EOF error can be produced if face specifications don't have the right structure, or are missing information (make sure your export settings are correct and include vertices, texture coordinates, and normals)");
                return false;
            }
            vertexIndices.push_back(vi0-1);   // x/o/o
            texcoordIndices.push_back(ti0-1); // o/x/o
            normalIndices.push_back(ni0-1);   // o/o/x

            vertexIndices.push_back(vi1-1);   // x/o/o
            texcoordIndices.push_back(ti1-1); // o/x/o
            normalIndices.push_back(ni1-1);   // o/o/x

            vertexIndices.push_back(vi2-1);   // x/o/o
            texcoordIndices.push_back(ti2-1); // o/x/o
            normalIndices.push_back(ni2-1);   // o/o/x
        } else { // TODO: Implement ifs for all possible headers (including comment), then add error if unknown header is reached
            CPPML_TRACE("In method \"LoadOBJFile\". Line header of line {} was ignored: \"{}\"", currentLine, header);
            if(ScanTillNewline(file) == EOF) { // reads till new-line, effectively skips to next line
                break;
            }
        }
        currentLine++;
    }
    CPPML_TRACE("In method \"LoadOBJFile\". Reached EOF.");

    vertexCount = vertexIndices.size();
    ret_vertices = std::make_unique<float[]>(vertexCount*3);
    ret_texcoords = std::make_unique<float[]>(vertexCount*2);
    ret_normals = std::make_unique<float[]>(vertexCount*3);

    for(size_t i=0; i<vertexCount; i++) {
        ret_vertices[(i*3)] = tempVertices[vertexIndices[i]][0];
        ret_vertices[(i*3)+1] = tempVertices[vertexIndices[i]][1];
        ret_vertices[(i*3)+2] = tempVertices[vertexIndices[i]][2];

        ret_texcoords[(i*2)] = tempTexcoords[texcoordIndices[i]][0];
        ret_texcoords[(i*2)+1] = tempTexcoords[texcoordIndices[i]][1];

        ret_normals[(i*3)] = tempNormals[normalIndices[i]][0];
        ret_normals[(i*3)+1] = tempNormals[normalIndices[i]][1];
        ret_normals[(i*3)+2] = tempNormals[normalIndices[i]][2];
    }

    return true;
}

}
