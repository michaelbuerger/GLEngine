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

void ShaderProgram::Uniform(const GLchar* name, const GLfloat &value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name), value);
}
void ShaderProgram::Uniform(const GLchar* name, const GLint &value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void ShaderProgram::Uniform(const GLchar* name, const GLuint &value) const
{
    glUniform1ui(glGetUniformLocation(m_ID, name), value);
}
void ShaderProgram::Uniform(const GLchar* name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));
}
void ShaderProgram::Uniform(const GLchar* name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::Bind()
{
    glUseProgram(m_ID);
}
}
