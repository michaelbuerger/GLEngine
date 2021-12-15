#ifndef GLE_SHADER_PROGRAM_HPP
#define GLE_SHADER_PROGRAM_HPP

#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/io/io.hpp"

#include "glm/glm.hpp"

namespace GLEngine
{
class ShaderProgram
{
public:
    ShaderProgram(const GLuint &shaderProgramID);
    ShaderProgram(const GLuint &vertexShaderID, const GLuint &fragmentShaderID, const bool &shouldDeleteShaders);
    ShaderProgram(const GLchar *vertexShaderAddress, const char *fragmentShaderAddress);

    void UniformBool(const GLchar* name, const bool &value) const;
    void UniformFloat(const GLchar* name, const GLfloat &value) const;
    void UniformInt(const GLchar* name, const GLint &value) const;
    void UniformUint(const GLchar* name, const GLuint &value) const;
    void UniformVec2(const GLchar* name, const glm::vec2 &value) const;
    void UniformVec3(const GLchar* name, const glm::vec3 &value) const;
    void UniformMat4(const GLchar* name, const glm::mat4 &value) const;

    void Bind() const;
    void Unbind() const;

    GLuint GetID() const;
private:
    GLuint m_ID;
};
}

#endif