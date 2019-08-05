#include "GLEngine/graphics/Model.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <memory>
#include <utility>

namespace GLEngine
{

Model::Model(const GLuint &vao, const GLuint &vertexCount, const std::shared_ptr<Texture> &texture)
{
    m_vao = vao;
    m_texture = texture;
    m_vertexCount = vertexCount;
}
Model::Model(const Model &model)
{
    m_vao = model.GetVAO();
    m_texture = model.GetTexture();
    m_vertexCount = model.GetVertexCount();
}

GLuint Model::GetVAO() const
{
    return m_vao;
}
const std::shared_ptr<Texture> &Model::GetTexture() const
{
    return m_texture;
}
GLuint Model::GetVertexCount() const
{
    return m_vertexCount;
}

void Model::BindVAO() const
{
    glBindVertexArray(m_vao);
}
void Model::UnbindVAO() const
{
    glBindVertexArray(0);
}

void Model::BindTexture() const
{
    m_texture->Bind();
}
void Model::UnbindTexture() const
{
    m_texture->Unbind();
}

/* Bind vao and texture */
void Model::Bind() const
{
    this->BindVAO();
    this->BindTexture();
}
/* Unbind vao and texture */
void Model::Unbind() const
{
    this->UnbindVAO();
    this->UnbindTexture();
}

} // namespace GLEngine