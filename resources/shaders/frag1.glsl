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
uniform vec3 viewPos; // camera position

//vec3 CalcDirectionalLight(DirectionalLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor);
vec3 CalcPointLight(PointLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, vec3 viewDir);

void main()
{
  vec3 ambientColor;
  vec3 diffuseColor;
  vec3 specularColor;

  ambientColor = vec3(texture(material.diffuseMap, texCoord));
  diffuseColor = vec3(texture(material.diffuseMap, texCoord));
  specularColor = vec3(texture(material.specularMap, texCoord));

  vec3 viewDir = normalize(viewPos - fragPos);

  vec3 result = vec3(0.0, 0.0, 0.0);

  //for(int i=0; i < NUM_DIRECTIONAL_LIGHTS; i++)
  //{
  //  result += CalcDirectionalLight(directionalLight[i], ambientColor, diffuseColor, specularColor);
  //}

  for(int i=0; i < NUM_POINT_LIGHTS; i++)
  {
    result += CalcPointLight(pointLight[i], ambientColor, diffuseColor, specularColor, viewDir);
  }

  fragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, vec3 viewDir)
{
  vec3 lightPos = light.position;

  vec3 lightDir = normalize(lightPos - fragPos);
  // diffuse
  float diff = max(dot(normal, lightDir), 0.0);

  //specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // attenuation
  float distance = length(lightPos - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec3 ambient = light.ambientMultiplier * ambientColor;
  vec3 diffuse = light.diffuseMultiplier * diffuseColor;
  vec3 specular = light.specularMultiplier * specularColor;

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
} 