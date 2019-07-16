// http://paulbourke.net/dataformats/obj/
// https://en.wikipedia.org/wiki/Wavefront_.obj_file

/* Figure out way to generate texcoords and normals */

#include "GLEngine/graphics/ModelHandler.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/io/io.hpp"

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace GLEngine { namespace graphics {

    GLfloat square_vertices_texcoords_normals[]
    {
        1.0f, 1.0f, 0.0f,    1.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top-right
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom-right
        -1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top-left
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f  // bottom-left
    };

    GLint square_indices[]
    {
        2, 1, 3, 0, 1, 2
    };

    void LoadOBJFile(const char* address, std::unique_ptr<GLfloat[]>& ret_data, std::unique_ptr<GLuint[]>& ret_indices, GLuint& ret_vertexCount, GLsizeiptr& ret_dataSize, GLsizeiptr& ret_indicesSize)
    {
        /* std::stof converts std::string to float, contained in <string>, doesn't care about spaces before and after num */
        std::ifstream file(address);

        if(file.is_open() == false)
        {
            std::cout << "Could not open model at \"" << address << "\"" << std::endl;
            throw GLE_CANT_OPEN_FILE();
            return;
        }

        std::string line;

        std::vector<std::array<GLfloat, 3>> vertexDict = std::vector<std::array<GLfloat, 3>>();
        std::vector<std::array<GLfloat, 2>> texcoordDict = std::vector<std::array<GLfloat, 2>>();
        std::vector<std::array<GLfloat, 3>> normalDict = std::vector<std::array<GLfloat, 3>>();
        std::vector<std::array<GLuint, 3>> vtnComboDict = std::vector<std::array<GLuint, 3>>();
        std::vector<GLuint> comboIndices;
        GLuint comboIndex = 0;
        
        while (std::getline(file, line))
        {
            //std::cout << "---LINE: " << line << " ---" << std::endl; // DEBUG
            if(line[0] == 'v') // per-vertex data
            {
                if(line[1] == 't') // texcoord
                {
                    GLuint numsFound = 0;
                    std::string numStr = "";
                    std::array<GLfloat, 2> grp = std::array<GLfloat, 2>();
                    GLuint grpi = 0;
                    for(size_t i=3; i<line.size(); i++)
                    {
                        if(i == line.size()-1)
                        {
                            numStr += line[i];
                        }
                        if(line[i] == ' ' || i == line.size()-1)
                        {
                            grp[grpi] = std::stof(numStr);
                            grpi++;
                            numsFound++;
                            numStr = "";

                            if(numsFound == 2)
                            {
                                break;
                            }
                            continue;
                        }

                        if(i != line.size()-1)
                        {
                            numStr += line[i];
                        }
                    }
                    texcoordDict.push_back(grp);
                } else if(line[1] == 'n') // normal
                {
                    GLuint numsFound = 0;
                    std::string numStr = "";
                    std::array<GLfloat, 3> grp = std::array<GLfloat, 3>();
                    GLuint grpi = 0;
                    for(size_t i=3; i<line.size(); i++)
                    {
                        if(i == line.size()-1)
                        {
                            numStr += line[i];
                        }
                        if(line[i] == ' ' || i == line.size()-1) {
                            grp[grpi] = std::stof(numStr);
                            grpi++;
                            numsFound++;
                            numStr = "";
                            if(numsFound == 3)
                            {
                                break;
                            }
                            continue;
                        }
                        if(i != line.size()-1)
                        {
                            numStr += line[i];
                        }

                    }
                    normalDict.push_back(grp);
                } else // vertex
                {
                    GLuint numsFound = 0;
                    std::string numStr = "";
                    std::array<GLfloat, 3> grp = std::array<GLfloat, 3>();
                    GLuint grpi = 0;
                    for(size_t i=2; i<line.size(); i++)
                    {
                        if(i == line.size()-1)
                        {
                            numStr += line[i];
                        }
                        if(line[i] == ' ' || i == line.size()-1)
                        {
                            grp[grpi] = std::stof(numStr);
                            grpi++;
                            numsFound++;
                            numStr = "";
                            if(numsFound == 3)
                            {
                                break;
                            }
                            continue;
                        }
                        if(i != line.size()-1)
                        {
                            numStr += line[i];
                        }
                    }
                    vertexDict.push_back(grp);
                }
                
            } else if(line[0] == 'f') // face specification
            {

                GLuint numsFound = 0;
                std::string numStr = "";
                std::array<GLuint, 3> vtnCombo = std::array<GLuint, 3>();
                GLuint vtnComboi = 0;
                for(size_t i=2; i<line.size(); i++)
                {
                    if(line[i] == '/')
                    {
                        vtnCombo[vtnComboi] = std::stoi(numStr);
                        vtnComboi++;
                        numsFound++;
                        numStr = "";
                        continue;
                    }
                    
                    if(numsFound == 2 && line[i] == ' ')
                    {
                        vtnCombo[vtnComboi] = std::stoi(numStr);
                        vtnComboi = 0;
                        numsFound = 0;
                        numStr = "";

                        // handle vtn combo

                        int foundIndex = -1;
                        // check if vtn combo is in dict already
                        for(size_t vi=0; vi<vtnComboDict.size(); vi++)
                        {
                            std::array<GLuint, 3> vtnComboVI = vtnComboDict.at(vi);
                            // compare
                            if(vtnComboVI[0] == vtnCombo[0] && vtnComboVI[1] == vtnCombo[1] && vtnComboVI[2] == vtnCombo[2])
                            {
                                // found
                                foundIndex = vi;
                                break;
                            }
                        }

                        if(foundIndex == -1) {
                            foundIndex = comboIndex;
                            vtnComboDict.push_back(vtnCombo);
                            comboIndex++;
                        }

                        comboIndices.push_back(foundIndex);
                        continue;
                    }

                    numStr += line[i];
                }
            } else // comment or other line that isn't used
            {
                continue;
            }
        }

        file.close();

        ret_data = std::make_unique<GLfloat[]>(vtnComboDict.size()*8);
        ret_indices = std::make_unique<GLuint[]>(comboIndices.size());
        ret_dataSize = vtnComboDict.size() * 8 * sizeof(GLfloat);
        ret_indicesSize = comboIndices.size() * sizeof(GLuint);
        ret_vertexCount = comboIndices.size();

        for(size_t i=0;i<vtnComboDict.size();i++)
        {
            ret_data[i*8] = vertexDict.at(vtnComboDict[i][0]-1)[0];
            ret_data[(i*8)+1] = vertexDict.at(vtnComboDict[i][0]-1)[1];
            ret_data[(i*8)+2] = vertexDict.at(vtnComboDict[i][0]-1)[2];
            ret_data[(i*8)+3] = texcoordDict.at(vtnComboDict[i][1]-1)[0];
            ret_data[(i*8)+4] = texcoordDict.at(vtnComboDict[i][1]-1)[1];
            ret_data[(i*8)+5] = normalDict.at(vtnComboDict[i][2]-1)[0];
            ret_data[(i*8)+6] = normalDict.at(vtnComboDict[i][2]-1)[1];
            ret_data[(i*8)+7] = normalDict.at(vtnComboDict[i][2]-1)[2];
        }

        for(size_t i=0;i<comboIndices.size();i++)
        {
            ret_indices.get()[i] = comboIndices[i];
        }
    }

    GLuint CreateVAO(const GLfloat data[], const GLuint indices[], const GLsizeiptr& dataSizeBytes, const GLsizeiptr& indicesSizeBytes, const GLuint& drawMode)
    {
        GLuint vao, vbo, elementBuffer;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &elementBuffer);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

        glBufferData(GL_ARRAY_BUFFER, dataSizeBytes, data, drawMode);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeBytes, indices, drawMode);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);                     // vertices
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // texcoords
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat))); // normals
        // TODO: Add support for data structure differing from the following: 3D vertices, 2D texcoords, 3D normals

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        return vao;
    }

}}