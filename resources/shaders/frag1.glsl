#version 330 core

in vec2 texCoord;
in vec3 normal;

in vec3 pointLightPos;

in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D texture2D;

void main()
{
  float ambientStrength = 0.15;
  float specularStrength = 0.5;
  float shininess = 128; // lower -> higher = rougher to smoother (how much the specular highlight is diffused less -> more)
  vec3 lightColor = vec3(1.0, 1.0, 1.0);

  // Ambient
  vec3 ambient = ambientStrength * lightColor;

  // Diffuse
  vec3 lightDirection = normalize(pointLightPos - fragPos); 
  vec3 normalizedNormal = normalize(normal);
  // Note: lightDirection is slightly misleading because it is actually a direction vector from the fragPos to the point light
  float diff = max(dot(normalizedNormal, lightDirection), 0.0);
  vec3 diffuse = diff * lightColor;

  // Specular
  vec3 viewDirection = normalize(vec3(0, 0, 0) - fragPos); // Note 0, 0, 0 is the camera/viewer's position as lighting variables are transformed into model-view space
  vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
  vec3 specular = specularStrength * spec * lightColor;

  vec3 lighting = ambient + diffuse + specular;

  fragColor = vec4(lighting, 1.0) * texture(texture2D, texCoord);
}




