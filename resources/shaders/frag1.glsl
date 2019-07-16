#version 330 core

in vec2 texCoord;
in vec4 randomColor;

out vec4 fragColor;

uniform sampler2D texture2D;

void main()
{
  //fragColor = (1.0, 1.0, 1.0, 1.0) * texture(texture2D, texCoord));
  fragColor = randomColor;

}




