#include "GLEngine/graphics/Model.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <memory>
#include <utility>

namespace GLEngine
{

Model::Model(const GLuint &vao, const GLuint &indicesCount)
{
    m_vao = vao;
    m_indices = indicesCount;
}
Model::Model(const Model &model)
{
    m_vao = model.GetVAO();
    m_indices = model.GetIndicesCount();
}

GLuint Model::GetVAO() const
{
    return m_vao;
}

GLuint Model::GetIndicesCount() const
{
    return m_indices;
}

void Model::Bind() const
{
    glBindVertexArray(m_vao);
}

// if transforms size grows OR transforms data has not been uploaded before, create dynamic vertex buffer for transform data
// then upload data to dynamic vertex buffer
void Model::UploadInstanceData(const glm::mat4* transformMatrixArrayPtr, const GLuint &transformsCount)
{
    if(transformsCount > 0)
    {
        this->Bind();

        if(transformsCount > m_instances) // buffer has not been set up yet or needs to grow (growing constantly = major performance issues)
        {
            m_instances = transformsCount;
            glGenBuffers(1, &m_instanceMatrixBuffer); // generate vertex buffer for instanceMatrixBuffer

            glBindBuffer(GL_ARRAY_BUFFER, m_instanceMatrixBuffer); // bind vertex position vbo
            glBufferData(GL_ARRAY_BUFFER, m_instances * sizeof(glm::mat4), transformMatrixArrayPtr, GL_DYNAMIC_DRAW); // copy transform matrices into data store on the GPU
            
            std::size_t vec4Size = sizeof(glm::vec4);

            glEnableVertexAttribArray(3); // matrices
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)0); // first vec4 (row/column)

            glEnableVertexAttribArray(4); // matrices
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)(1 * vec4Size)); // second vec4 (row/column)

            glEnableVertexAttribArray(5); // matrices
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)(2 * vec4Size)); // third vec4 (row/column)

            glEnableVertexAttribArray(6); // matrices
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)(3 * vec4Size)); // fourth vec4 (row/column)

            // increment every instance
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            std::cout << "Making instance matrix buffer" << std::endl;
        }else // buffer has been set up and doesn't need to grow, just needs to update transformation matrices
        {
            m_instances = transformsCount;
            glBindBuffer(GL_ARRAY_BUFFER, m_instanceMatrixBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_instances * sizeof(glm::mat4), transformMatrixArrayPtr); // can sub buffer data with an offset (TODO: make lazy calculations of transform matrices directly sub data?)
        }
    }
}

} // namespace GLEngine