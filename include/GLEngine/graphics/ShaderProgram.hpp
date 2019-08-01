#ifndef GLE_SHADER_PROGRAM_HPP
#define GLE_SHADER_PROGRAM_HPP

#include "GLEngine/graphics/graphics.hpp"

#include "glm/glm.hpp"

#include "GLEngine/io/io.hpp"

namespace GLEngine
{
class ShaderProgram
{
public:
    ShaderProgram(const GLuint &shaderProgramID);
    ShaderProgram(const GLuint &vertexShaderID, const GLuint &fragmentShaderID, const bool &shouldDeleteShaders);
    ShaderProgram(const GLchar *vertexShaderAddress, const char *fragmentShaderAddress);

    void Uniform(const GLchar* name, const GLfloat &value) const;
    void Uniform(const GLchar* name, const GLint &value) const;
    void Uniform(const GLchar* name, const GLuint &value) const;
    void Uniform(const GLchar* name, const glm::vec3 &value) const;
    void Uniform(const GLchar* name, const glm::mat4 &value) const;

    void Bind();
    void Unbind();

    GLuint GetID();
private:
    GLuint m_ID;
};
}

#endif