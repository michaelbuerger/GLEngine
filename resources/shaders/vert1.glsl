#version 330 core

layout (location = 0) in vec3 aPos; // vertex
layout (location = 1) in vec2 aTexCoord; // tex coord for given vertex
layout (location = 2) in vec3 aNormal;

uniform mat4 modelMatrix; // Transformation matrix for the model
uniform mat4 viewMatrix; // Inverse of camera's transform
uniform mat4 projectionMatrix; // Projection or orthographic, for scaling based on distance from camera
uniform mat4 normalMatrix; // 

out vec2 texCoord;
out vec3 normal;

out vec3 fragPos;

void main()
{
  // object/model space --> world space
  fragPos = vec3(modelMatrix * vec4(aPos, 1.0)); // send vertex in world space

  // world space --> "clip space"
  gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);

  texCoord = aTexCoord; // pass texcoord to fragment shader to be interpolated between vertices
  normal = mat3(normalMatrix) * aNormal; // send normal direction after rotation and potentially non-uniform scaling
}
