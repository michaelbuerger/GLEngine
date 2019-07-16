#version 330 core

layout (location = 0) in vec3 aPosModelspace;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 mvpMatrix;

out vec2 texCoord;
out vec4 randomColor;

float rand(vec2 co)
{
  return fract(sin(dot(co.xy, vec2(12.9898, 78.2233))) * 43758.5453);
}

void main()
{
  gl_Position = mvpMatrix * vec4(aPosModelspace, 1.0);
  texCoord = aTexCoord;
  randomColor = vec4(rand(vec2(aPosModelspace.x, aPosModelspace.y)), rand(vec2(aPosModelspace.y, aPosModelspace.z)), rand(vec2(aPosModelspace.y, aPosModelspace.x)), 1.0);
}
