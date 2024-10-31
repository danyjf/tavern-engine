#version 460 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

// BUILT-IN UNIFORMS ---------------------------------------------------------------
// If these uniforms are changed, the ShaderResource source code needs to be updated
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 lightPos;
uniform vec3 viewPos;
// ---------------------------------------------------------------------------------

uniform int isUnlit = 0;
uniform vec3 objectColor = vec3(0.0, 0.0, 0.0);
uniform int useTexture = 1;
uniform sampler2D texture1;

void main()
{
    vec3 color = objectColor;
    if (useTexture == 1) 
    {
        color = texture(texture1, TexCoord).rgb;
    }

    if (isUnlit == 0) {
        // Calculate ambient light
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        // Calculate diffuse light
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // Calculate Specular light
        float specularStrength = 0.5;

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;

        // Final color
        FragColor = vec4((ambient + diffuse + specular) * color, 1.0);
    }
    else
    {
        FragColor = vec4(color, 1.0);
    }
}

