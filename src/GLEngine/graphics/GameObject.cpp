#include "GLEngine/graphics/GameObject.hpp"

namespace GLEngine
{
    GameObject::GameObject(const std::shared_ptr<Model> &model, const std::shared_ptr<Material> &material, const Transform &transform)
    {
        this->transform = transform; // hopefully this does an implicit copy
        this->model = model;
        this->material = material;
    }

    GameObject::GameObject(const std::shared_ptr<Model> &model, const std::shared_ptr<Material> &material)
    {
        this->transform = Transform();
        this->model = model;
        this->material = material;
    }

    void GameObject::Bind()
    {
        this->material->Bind();
        this->model->Bind();
        // TODO: make these uniform names not hard-coded
        this->material->shaderProgram->UniformMat4("modelMatrix", this->transform.GetMatrix());
        this->material->shaderProgram->UniformMat4("normalMatrix", this->transform.GetNormalMatrix());
    }

    void GameObject::BindSubShader(const std::shared_ptr<ShaderProgram> shaderProgram)
    {
        this->material->BindSubShader(shaderProgram);
        this->model->Bind();
        // TODO: make these uniform names not hard-coded
        shaderProgram->UniformMat4("modelMatrix", this->transform.GetMatrix());
        shaderProgram->UniformMat4("normalMatrix", this->transform.GetNormalMatrix());
    }
} // namespace GLEngine