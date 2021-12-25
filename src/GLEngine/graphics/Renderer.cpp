#include "GLEngine/graphics/Renderer.hpp"
#include "GLEngine/graphics/GameObject.hpp"
#include "GLEngine/graphics/graphics.hpp"

namespace GLEngine
{
    void Renderer::Init()
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void Renderer::Update()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear current framebuffer (should be back buffer of widnow) + depth buffer
    }

    void Renderer::Render(GameObject& gameObject)
    {
        gameObject.material->instanced = false;
        gameObject.Bind(); // bind material --> use shader program, bind model --> use vao
        // indices data nullptr as element array buffer (vbo) is expected within model (vao)
        glDrawElements(GL_TRIANGLES, gameObject.model->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    } 

    void Renderer::RenderInstanced(GameObject& gameObject, const glm::mat4* transformationMatricesArrayPtr, const uint& instances)
    {
        if(instances > 0)
        {
            // if transforms size grows OR transforms data has not been uploaded before, create dynamic vertex buffer for transform data
            // then upload data to dynamic vertex buffer
            gameObject.model->UploadInstanceData(transformationMatricesArrayPtr, instances);

            gameObject.material->instanced = true;
            gameObject.Bind();
            glDrawElementsInstanced(GL_TRIANGLES, gameObject.model->GetIndicesCount(), GL_UNSIGNED_INT, nullptr, instances);
        }
    }
}