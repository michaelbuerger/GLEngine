#include <glm/glm.hpp>

#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"

#ifndef GLE_MATERIAL_HPP
#define GLE_MATERIAL_HPP

namespace GLEngine
{

class Material
{
public:
    Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram);
    Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit);
    Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit, const float &shininess);
    Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit, const float &shininess, const bool &useTexture, const glm::vec3 &color);
private:
    void m_Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit, const float &shininess, const bool &useTexture, const glm::vec3 &color);
public:
    std::shared_ptr<Texture> diffuse;
    std::shared_ptr<Texture> specular;
    std::shared_ptr<ShaderProgram> shaderProgram;
    
    bool useTexture;
    glm::vec3 color; // to use if useTexture == false
    float shininess; // should be some power of 2
    bool unlit; // specifies whether lighting applies to material

public:
    void Bind();
    void Unbind();
};

}

#endif