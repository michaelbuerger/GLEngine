#version 420 core

in vec2 texCoord; // interpolated texcoord of given fragment
in vec3 fragPos;

out vec4 fragColor; // output color of given fragment (RGBA)

uniform sampler2D shadowMap;

void main()
{
  float depthValue = texture(shadowMap, texCoord).r;
  fragColor = vec4(vec3(depthValue), 1.0);
  //fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}