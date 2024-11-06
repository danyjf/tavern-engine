#version 460 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 albedo = vec3(1.0, 1.0, 1.0);
uniform sampler2D albedoMap;

void main()
{
    vec3 textureColor = texture(albedoMap, TexCoord).rgb;
    vec3 color = albedo * textureColor;

    FragColor = vec4(color, 1.0);
}

