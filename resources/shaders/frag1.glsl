#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texture2D;

void main()
{
  fragColor = texture(texture2D, texCoord);

}




