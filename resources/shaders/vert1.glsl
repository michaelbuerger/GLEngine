#version 330 core

layout (location = 0) in vec3 aPosModelspace;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 mvpMatrix;

out vec2 texCoord;

void main()
{
  gl_Position = mvpMatrix * vec4(aPosModelspace, 1.0);
  texCoord = aTexCoord;
}
