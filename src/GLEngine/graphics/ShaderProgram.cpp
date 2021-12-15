#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLEngine/io/io.hpp"

namespace GLEngine
{
ShaderProgram::ShaderProgram(const GLuint &shaderProgramID)
{
    m_ID = shaderProgramID;
}
ShaderProgram::ShaderProgram(const GLuint &vertexShaderID, const GLuint &fragmentShaderID, const bool &shouldDeleteShaders)
{
    m_ID = CreateShaderProgram(vertexShaderID, fragmentShaderID, shouldDeleteShaders);
}
ShaderProgram::ShaderProgram(const GLchar *vertexShaderAddress, const char *fragmentShaderAddress)
{
    m_ID = CreateShaderProgramFromAddresses(vertexShaderAddress, fragmentShaderAddress);
}

void ShaderProgram::UniformBool(const GLchar* name, const bool &value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void ShaderProgram::UniformFloat(const GLchar* name, const GLfloat &value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name), value);
}
void ShaderProgram::UniformInt(const GLchar* name, const GLint &value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void ShaderProgram::UniformUint(const GLchar* name, const GLuint &value) const
{
    glUniform1ui(glGetUniformLocation(m_ID, name), value);
}
void ShaderProgram::UniformVec2(const GLchar* name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));
}
void ShaderProgram::UniformVec3(const GLchar* name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));
}
void ShaderProgram::UniformMat4(const GLchar* name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::Bind() const
{
    glUseProgram(m_ID);
}

void ShaderProgram::Unbind() const // calling this is unnecessary, one can simply bind another program
{
    glUseProgram(0);
}

GLuint ShaderProgram::GetID() const
{
    return m_ID;
}
}
