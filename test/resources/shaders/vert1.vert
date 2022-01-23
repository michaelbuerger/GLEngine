#version 330 core

layout (location = 0) in vec3 aPos; // vertex
layout (location = 1) in vec2 aTexCoord; // tex coord for given vertex
layout (location = 2) in vec3 aNormal;
layout (location = 3) in mat4 instanceMatrix; // Transformation matrix for the model, used if instanced = true

uniform mat4 modelMatrix; // Transformation matrix for the model, used if instanced = false
uniform mat4 viewMatrix; // Inverse of camera's transform
uniform mat4 projectionMatrix; // Projection or orthographic, for scaling based on distance from camera
uniform mat4 normalMatrix;
uniform mat4 lightSpaceMatrix;

uniform bool instanced;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 fragPosLightSpace;

void main()
{
  if(!instanced)
  {
    // object/model space --> world space
    fragPos = vec3(modelMatrix * vec4(aPos, 1.0)); // send vertex in world space
  } else if(instanced)
  {
    // object/model space --> world space
    fragPos = vec3(instanceMatrix * vec4(aPos, 1.0));  // send vertex in world space
  }

  // world space --> "clip space"
  gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);

  texCoord = aTexCoord; // pass texcoord to fragment shader to be interpolated between vertices
  normal = mat3(normalMatrix) * aNormal; // send normal direction after rotation and potentially non-uniform scaling

  fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
}
