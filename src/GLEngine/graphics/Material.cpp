#include "GLEngine/graphics/Material.hpp"
#include "GLEngine/math/math.hpp"
#include "GLEngine/defines.hpp"

namespace GLEngine
{

    Material::Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram)
    {
        this->m_Material(diffuse, specular, shaderProgram, false, GLE_MATERIAL_DEFAULT_SHININESS, true, VEC3F_ZERO, false);
    }

    Material::Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit)
    {
        this->m_Material(diffuse, specular, shaderProgram, unlit, GLE_MATERIAL_DEFAULT_SHININESS, true, VEC3F_ZERO, false);
    }

    Material::Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit, const float &shininess)
    {
        this->m_Material(diffuse, specular, shaderProgram, unlit, shininess, true, VEC3F_ZERO, false);
    }

    Material::Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit, const float &shininess, const bool &useTexture, const glm::vec3 &color)
    {
        this->m_Material(diffuse, specular, shaderProgram, unlit, shininess, useTexture, color, false);
    }

    Material::Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit, const float &shininess, const bool &useTexture, const glm::vec3 &color, const bool& instanced)
    {
        this->m_Material(diffuse, specular, shaderProgram, unlit, shininess, useTexture, color, instanced);
    }

    void Material::m_Material(const std::shared_ptr<Texture> &diffuse, const std::shared_ptr<Texture> &specular, const std::shared_ptr<ShaderProgram> &shaderProgram,
            const bool &unlit, const float &shininess, const bool &useTexture, const glm::vec3 &color, const bool& instanced)
    {
        this->diffuse = diffuse;
        this->specular = specular;
        this->shaderProgram = shaderProgram;
        this->unlit = unlit;
        this->shininess = shininess;
        this->useTexture = useTexture;
        this->color = color;
        this->tiling = glm::vec2(1, 1);
        this->instanced = instanced;
    }

    void Material::Bind() const
    {
        this->shaderProgram->Bind();

        if(useTexture)
        {
            this->shaderProgram->UniformInt("material.diffuseMap", GLE_MATERIAL_DIFFUSE_UNIFORM_ID); // specify texture slot of diffuse map
            this->shaderProgram->UniformInt("material.specularMap", GLE_MATERIAL_SPECULAR_UNIFORM_ID); // specify texture slot of specular map
            this->shaderProgram->UniformVec2("material.tiling", this->tiling);
            
            if(this->diffuse != nullptr)
            {
                this->diffuse->Bind(GLE_MATERIAL_DIFFUSE_TEX_SLOT);
            }

            if(this->specular != nullptr)
            {
                this->specular->Bind(GLE_MATERIAL_SPECULAR_TEX_SLOT);
            }
        } else
        { // useTexture == false --> replace diffuse with color and specular with (1.0f, 1.0f, 1.0f) (in shader)
            this->shaderProgram->UniformVec3("material.color", this->color);
        }

        this->shaderProgram->UniformBool("material.unlit", this->unlit);
        this->shaderProgram->UniformFloat("material.shininess", this->shininess);
        this->shaderProgram->UniformBool("material.useTexture", this->useTexture);

        this->shaderProgram->UniformBool("instanced", this->instanced);
    }

    void Material::BindSubShader(const std::shared_ptr<ShaderProgram> shaderProgram) const
    {
        shaderProgram->Bind();

        if(useTexture)
        {
            shaderProgram->UniformInt("material.diffuseMap", GLE_MATERIAL_DIFFUSE_UNIFORM_ID); // specify texture slot of diffuse map
            shaderProgram->UniformInt("material.specularMap", GLE_MATERIAL_SPECULAR_UNIFORM_ID); // specify texture slot of specular map
            shaderProgram->UniformVec2("material.tiling", this->tiling);
            
            if(this->diffuse != nullptr)
            {
                this->diffuse->Bind(GLE_MATERIAL_DIFFUSE_TEX_SLOT);
            }

            if(this->specular != nullptr)
            {
                this->specular->Bind(GLE_MATERIAL_SPECULAR_TEX_SLOT);
            }
        } else
        { // useTexture == false --> replace diffuse with color and specular with (1.0f, 1.0f, 1.0f) (in shader)
            shaderProgram->UniformVec3("material.color", this->color);
        }

        shaderProgram->UniformBool("material.unlit", this->unlit);
        shaderProgram->UniformFloat("material.shininess", this->shininess);
        shaderProgram->UniformBool("material.useTexture", this->useTexture);

        shaderProgram->UniformBool("instanced", this->instanced);
    }

} // namespace GLEngine