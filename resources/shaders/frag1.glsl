#version 330 core

in vec2 texCoord;
in vec3 normal;

in vec3 fragPos;

out vec4 fragColor;

uniform vec3 color;
uniform sampler2D texture2D;
uniform float shininess;

in vec3 pointLightPos;
uniform float lightStrength = 1.0;
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform float ambientStrength = 0.15;
uniform float diffuseStrength = 0.7;
uniform float specularStrength = 0.15;

void main()
{
  float lightStrength = 1.0;
  vec3 lightColor = vec3(1.0, 1.0, 1.0);
  float ambientStrength = 0.15;
  float diffuseStrength = 0.7;
  float specularStrength = 0.15;
  float shininess = 1; // lower -> higher = rougher to smoother
  bool unlit = false;

  // Ambient
  vec3 ambient = ambientStrength * lightColor;

  // Diffuse
  vec3 lightDirection = normalize(pointLightPos - fragPos); 
  vec3 normalizedNormal = normalize(normal);
  // Note: lightDirection is slightly misleading because it is actually a direction vector from the fragPos to the point light
  float diff = max(dot(normalizedNormal, lightDirection), 0.0);
  vec3 diffuse = diffuseStrength * diff * lightColor;

  // Specular
  vec3 viewDirection = normalize(vec3(0, 0, 0) - fragPos); // Note 0, 0, 0 is the camera/viewer's position as lighting variables are transformed into model-view space
  vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
  vec3 specular = specularStrength * spec * lightColor;

  vec3 lighting = ambient + diffuse + specular;

  if(!unlit) {
    fragColor = vec4(lighting, 1.0) * texture(texture2D, texCoord);
  } else {
    fragColor = texture(texture2D, texCoord);
  }
}




