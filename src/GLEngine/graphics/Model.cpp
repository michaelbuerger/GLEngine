#include "GLEngine/graphics/Model.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <memory>
#include <utility>

namespace GLEngine
{

Model::Model(const GLuint &vao, const GLuint &vertexCount)
{
    m_vao = vao;
    m_vertexCount = vertexCount;
}
Model::Model(const Model &model)
{
    m_vao = model.GetVAO();
    m_vertexCount = model.GetVertexCount();
}

GLuint Model::GetVAO() const
{
    return m_vao;
}

GLuint Model::GetVertexCount() const
{
    return m_vertexCount;
}

void Model::Bind() const
{
    glBindVertexArray(m_vao);
}

void Model::Unbind() const
{
    glBindVertexArray(0);
}

} // namespace GLEngine