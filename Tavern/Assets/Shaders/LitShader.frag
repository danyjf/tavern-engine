#version 460 core

layout (location = 0) out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

// BUILT-IN UNIFORMS ---------------------------------------------------------------
// If these uniforms are changed, the ShaderResource source code needs to be updated
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 lightPos;
uniform vec3 viewPos;
// ---------------------------------------------------------------------------------

uniform vec3 ambient = vec3(0.1, 0.1, 0.1);
uniform vec3 albedo = vec3(1.0, 1.0, 1.0);
uniform vec3 specular = vec3(0.5, 0.5, 0.5);
uniform float shininess = 32.0f;

uniform sampler2D albedoMap;

void main()
{
    vec3 textureColor = texture(albedoMap, TexCoord).rgb;
    vec3 color = albedo * textureColor;

    // Calculate ambient light
    vec3 ambientColor = lightColor * ambient * color;

    // Calculate diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseColor = lightColor * diff * color;

    // Calculate Specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specularColor = lightColor * spec * specular;

    // Final color
    vec3 result = ambientColor + diffuseColor + specularColor;
    FragColor = vec4(result, 1.0);
}

