#ifndef GLE_RENDERER_HPP
#define GLE_RENDERER_HPP

#include "GLEngine/graphics/GameObject.hpp"

namespace GLEngine
{

class Renderer
{
public:
    static void Init();
    static void Update();

    static void Render(GameObject& gameObject);
    static void RenderInstanced(GameObject& gameObject, const glm::mat4* transformationMatricesArrayPtr, const uint& instances);

    static bool subShaderProgram;
    static std::shared_ptr<ShaderProgram> shaderProgramSubstitutePtr;
};

} // namespace GLEngine

#endif
