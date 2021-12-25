#ifndef GLE_MODEL_HPP
#define GLE_MODEL_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Transform.hpp"

#include <memory>
#include <utility>

namespace GLEngine
{

class Model
{
public:
    // Model(); // Create model with some primitive
    // Model(const GLuint& vao); // Create model with vao
    Model(const GLuint &vao, const GLuint &indicesCount);
    Model(const Model &model);

    GLuint GetVAO() const;
    GLuint GetIndicesCount() const;

    void Bind() const;

    void UploadInstanceData(const glm::mat4* transformMatrixArrayPtr, const GLuint &transformsCount);

private:
    GLuint m_vao;
    GLuint m_indices;

    GLuint m_instances = 0; // under normal circumstances these are irrelevant
    GLuint m_instanceMatrixBuffer;
};

} // namespace GLEngine

#endif