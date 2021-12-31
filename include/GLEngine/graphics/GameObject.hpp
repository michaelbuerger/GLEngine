#ifndef GLE_GAME_OBJECT_HPP
#define GLE_GAME_OBJECT_HPP

#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/graphics/Model.hpp"
#include "GLEngine/graphics/Material.hpp"

namespace GLEngine
{

class GameObject
{
public: // constructors
    GameObject(const std::shared_ptr<Model> &model, const std::shared_ptr<Material> &material, const Transform &transform);
    GameObject(const std::shared_ptr<Model> &model, const std::shared_ptr<Material> &material);

public: // public elements
    Transform transform;
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;

private: // private elements

public: // public methods
    void Bind();
    void BindSubShader(const std::shared_ptr<ShaderProgram> shaderProgram);

private: // private methods
};

} // namespace GLEngine

#endif