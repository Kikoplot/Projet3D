#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    color = vec4(result, 1.0f);
}
