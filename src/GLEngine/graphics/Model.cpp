#include "GLEngine/graphics/Model.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <memory>
#include <utility>

namespace GLEngine { namespace graphics {

    /* Model::Model()
    {

    } */
    /* Model::Model(const GLuint& vao)
    {
        m_vao = vao;
        m_texture = std::make_shared<Texture>();
    } */
    Model::Model(const GLuint& vao, const GLuint& vertexCount, const std::shared_ptr<Texture>& texture)
    {
        m_vao = vao;
        m_texture = texture;
        m_vertexCount = vertexCount;
    }
    Model::Model(const Model& model)
    {
        m_vao = model.GetVAO();
        m_texture = model.GetTexture();
        m_vertexCount = model.GetVertexCount();
    }

    GLuint Model::GetVAO() const
    {
        return m_vao;
    }
    const std::shared_ptr<Texture>& Model::GetTexture() const
    {
        return m_texture;
    }
    GLuint Model::GetVertexCount() const
    {
        return m_vertexCount;
    }


    /* Bind vao and texture */
    void Model::Bind() const
    {
        glBindVertexArray(m_vao);
        m_texture->Bind();
    }
    /* Unbind vao and texture */
    void Model::Unbind() const
    {
        glBindVertexArray(0);
        m_texture->Unbind();
    }

}}