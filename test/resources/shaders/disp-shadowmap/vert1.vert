#version 330 core

layout (location = 0) in vec3 aPos; // vertex
layout (location = 1) in vec2 aTexCoord; // tex coord for given vertex

uniform mat4 modelMatrix; // Transformation matrix for the model, used if instanced = false
uniform mat4 viewMatrix; // Inverse of camera's transform
uniform mat4 projectionMatrix; // Projection or orthographic, for scaling based on distance from camera

out vec2 texCoord;
out vec3 fragPos;

void main()
{
    texCoord = aTexCoord; // pass texcoord to fragment shader to be interpolated between vertices
    fragPos = vec3(modelMatrix * vec4(aPos, 1.0));

    // world space --> "clip space"
    gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);
}
