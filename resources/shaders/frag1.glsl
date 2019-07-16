#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texture2D;

void main()
{
  //fragColor = (vec4(1.0, 1.0, 1.0, 1.0) * texture(texture2D, texCoord));
  fragColor = vec4(1.0, 1.0, 1.0, 1.0);

}




