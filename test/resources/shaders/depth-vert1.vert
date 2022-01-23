#version 330 core

layout (location = 0) in vec3 aPos; // vertex
//layout (location = 1) in vec2 aTexCoord; // tex coord for given vertex
//layout (location = 2) in vec3 aNormal;
layout (location = 3) in mat4 instanceMatrix; // Transformation matrix for the model, used if instanced = true

uniform mat4 modelMatrix; // Transformation matrix for the model, used if instanced = false
uniform mat4 lightSpaceMatrix;

uniform bool instanced;

void main()
{
    gl_Position = lightSpaceMatrix * (instanced ? instanceMatrix : modelMatrix) * vec4(aPos, 1.0);
} 