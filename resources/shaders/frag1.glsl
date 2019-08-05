#version 330 core

in vec2 texCoord;
in vec3 normal;

in vec3 fragPos;

out vec4 fragColor;

struct Material
{
  sampler2D diffuseMap;
  sampler2D specularMap;
  vec3 color; // !!! ignored right now !!!
  float shininess; // Doesn't matter if unlit == false
  bool useTexture; // !!! ignored right now !!!
  bool unlit; // !!! ignored right now !!!
};

uniform mat4 viewMatrix; // Inverse of camera's transform

struct DirectionalLight
{
  vec3 direction;
  vec3 color;
  vec3 ambientMultiplier;
  vec3 diffuseMultiplier;
  vec3 specularMultiplier;
};

struct PointLight // make array for every element
{
  vec3 position;
  vec3 color;
  vec3 ambientMultiplier;
  vec3 diffuseMultiplier;
  vec3 specularMultiplier;

  float constant; // attenuation stuff
  float linear;
  float quadratic; 
};

#define NUM_DIRECTIONAL_LIGHTS 1
#define NUM_POINT_LIGHTS 3

uniform Material material;

uniform DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHTS];
uniform PointLight pointLight[NUM_POINT_LIGHTS];

vec3 CalcDirectionalLight(DirectionalLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor);
vec3 CalcPointLight(PointLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor);

void main()
{
  vec3 ambientColor;
  vec3 diffuseColor;
  vec3 specularColor;

  ambientColor = vec3(texture(material.diffuseMap, texCoord));
  diffuseColor = vec3(texture(material.diffuseMap, texCoord));
  specularColor = vec3(texture(material.specularMap, texCoord));

  vec3 result;

  for(int i=0; i < NUM_DIRECTIONAL_LIGHTS; i++)
  {
    result += CalcDirectionalLight(directionalLight[i], ambientColor, diffuseColor, specularColor);
  }

  for(int i=0; i < NUM_POINT_LIGHTS; i++)
  {
    //result += CalcPointLight(pointLight[i], ambientColor, diffuseColor, specularColor);
  }

  fragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  
  vec3 lightDirection = normalize(-light.direction);
  // Diffuse
  float diff = max(dot(normalize(normal), lightDirection), 0.0);
  // Specular
  vec3 viewDirection = normalize(vec3(0, 0, 0) - fragPos); // Note 0, 0, 0 is the camera/viewer's position as lighting variables are transformed into model-view space
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

  ambient = light.ambientMultiplier * ambientColor;
  diffuse = light.diffuseMultiplier * diff * diffuseColor;
  specular = light.specularMultiplier * spec * specularColor;

  return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  // Ambient
  ambient = light.ambientMultiplier * vec3(ambientColor) * light.color;

  // Diffuse
  vec3 lightDirection = normalize(vec3(viewMatrix * vec4(light.position, 1.0)) - fragPos); 
  vec3 normalizedNormal = normalize(normal);
  // Note: lightDirection is slightly misleading because it is actually a direction vector from the fragPos to the point light
  float diff = max(dot(normalizedNormal, lightDirection), 0.0);
  diffuse = light.diffuseMultiplier * vec3(diffuseColor) * diff * light.color;

  // Specular
  vec3 viewDirection = normalize(vec3(0, 0, 0) - fragPos); // Note 0, 0, 0 is the camera/viewer's position as lighting variables are transformed into model-view space
  vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
  specular = light.specularMultiplier * vec3(specularColor) * spec * light.color;

  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

  return (ambient + diffuse + specular) * attenuation;
} 