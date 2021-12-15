#version 330 core

in vec2 texCoord; // interpolated texcoord of given fragment
in vec3 normal; // normal of given fragment (same for whole face, probably different for NURBS)

in vec3 fragPos; // position of fragment in world space

out vec4 fragColor; // output color of given fragment (RGBA)

struct Material
{
  sampler2D diffuseMap;
  sampler2D specularMap;
  vec3 color;
  float shininess;
  bool useTexture;
  bool unlit;
  vec2 tiling;
};

struct DirectionalLight
{
  vec3 direction;

  vec3 ambientMultiplier;
  vec3 diffuseMultiplier;
  vec3 specularMultiplier;
};

struct PointLight // make array for every element
{
  vec3 position;

  vec3 ambientMultiplier;
  vec3 diffuseMultiplier;
  vec3 specularMultiplier;

  float constant; // attenuation stuff
  float linear;
  float quadratic; 
};

struct SpotLight
{
  vec3 position;
  vec3 direction;
  float cutoff; // inner cone
  float cutoffOuter; // outer cone (set to the same as inner cone to create a hard boundary around spot light)

  vec3 ambientMultiplier;
  vec3 diffuseMultiplier;
  vec3 specularMultiplier;

  float constant; // attenuation stuff
  float linear;
  float quadratic; 
};

#define MAX_DIRECTIONAL_LIGHTS 16 // for array sizing, should generally oversize these
#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 16

uniform int directionalLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

uniform Material material;

uniform DirectionalLight directionalLight[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform SpotLight spotLight[MAX_SPOT_LIGHTS];

uniform vec3 viewPos; // camera position

vec3 CalcDirectionalLight(DirectionalLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor);
vec3 CalcPointLight(PointLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor);
vec3 CalcSpotLight(SpotLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor);

void main()
{
  vec3 ambientColor;
  vec3 diffuseColor;
  vec3 specularColor;

  if(material.useTexture)
  {
    // ambientColor = vec3(texture(material.diffuseMap, texCoord));
    diffuseColor = vec3(texture(material.diffuseMap, texCoord*material.tiling));
    ambientColor = diffuseColor;
    specularColor = vec3(texture(material.specularMap, texCoord*material.tiling));
  } else
  {
    diffuseColor = material.color;
    ambientColor = material.color;
    specularColor = vec3(1.0, 1.0, 1.0);
  }

  vec3 result = vec3(0.0, 0.0, 0.0);

  if(material.unlit == false)
  {
    int directionalLightCountClamped = clamp(directionalLightCount, 0, MAX_DIRECTIONAL_LIGHTS);
    int pointLightCountClamped = clamp(pointLightCount, 0, MAX_POINT_LIGHTS);
    int spotLightCountClamped = clamp(spotLightCount, 0, MAX_SPOT_LIGHTS);

    for(int i=0; i < directionalLightCountClamped; i++)
    {
      result += CalcDirectionalLight(directionalLight[i], ambientColor, diffuseColor, specularColor);
    }

    for(int i=0; i < pointLightCountClamped; i++)
    {
      result += CalcPointLight(pointLight[i], ambientColor, diffuseColor, specularColor);
    }

    for(int i=0; i < spotLightCountClamped; i++)
    {
      result += CalcSpotLight(spotLight[i], ambientColor, diffuseColor, specularColor);
    }
  } else
  {
    result = diffuseColor;
  }

  fragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
{
  vec3 lightDir = normalize(-light.direction);
  vec3 norm = normalize(normal);

  // diffuse
  float diff = max(dot(norm, lightDir), 0.0);

  // specular
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec3 ambient = light.ambientMultiplier * ambientColor;
  vec3 diffuse = diff * light.diffuseMultiplier * diffuseColor;
  vec3 specular = spec * light.diffuseMultiplier * specularColor;

  return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
{
  vec3 lightPos = light.position;
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);

  // diffuse
  float diff = max(dot(norm, lightDir), 0.0);

  //specular
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  
  // attenuation
  float distance = length(lightPos - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec3 ambient = light.ambientMultiplier * ambientColor;
  vec3 diffuse = diff * light.diffuseMultiplier * diffuseColor * attenuation;
  vec3 specular = spec * light.specularMultiplier * specularColor * attenuation;

  return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
{
  vec3 lightPos = light.position;

  // direction based on light pos and frag pos
  // light.direction is intended direction of spot light
  vec3 lightDir = normalize(lightPos - fragPos);

  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = light.cutoff - light.cutoffOuter;
  float intensity = clamp((theta - light.cutoffOuter) / epsilon, 0.0, 1.0);

  vec3 norm = normalize(normal);

  // diffuse
  float diff = max(dot(norm, lightDir), 0.0);

  // specular
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec3 ambient = light.ambientMultiplier * ambientColor;
  vec3 diffuse = diff * light.diffuseMultiplier * diffuseColor * attenuation * intensity;
  vec3 specular = spec * light.specularMultiplier * specularColor * attenuation * intensity;

  return ambient + diffuse + specular;
}