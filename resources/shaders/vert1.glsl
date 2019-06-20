#version 330 core

layout (location = 0) in vec3 posModelspace;
uniform mat4 mvpMatrix;

out vec4 vertexColor; // to fragment shader

void main()
{
  gl_Position = mvpMatrix * vec4(posModelspace, 1.0);
  vertexColor = vec4(1.0, 1.0, 1.0, 1.0); // red
}
