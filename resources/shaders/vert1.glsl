#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 modelMatrix; // Transformation matrix of the model
uniform mat4 viewMatrix; // Inverse of camera's transform
uniform mat4 projectionMatrix; // Projection or orthographic, for scaling based on distance from camera
uniform mat4 normalMatrix;

out vec2 texCoord;
out vec3 normal;

out vec3 fragPos; // position of vertex in modelSpace. TODO: Find out if OpenGL interpolates these per fragment

void main()
{
  fragPos = vec3(modelMatrix * vec4(aPos, 1.0));
  gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);

  texCoord = aTexCoord;
  normal = mat3(normalMatrix) * aNormal;
}
