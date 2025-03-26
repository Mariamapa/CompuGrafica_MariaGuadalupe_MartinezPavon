#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform Light light2;

uniform sampler2D texture_diffusse;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 texColor = texture(texture_diffusse, TexCoords).rgb;

    // --- Primera luz ---
    vec3 lightDir1 = normalize(light.position - FragPos);
    float diff1 = max(dot(norm, lightDir1), 0.0);
    vec3 reflectDir1 = reflect(-lightDir1, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0), material.shininess);

    vec3 ambient1 = light.ambient * texColor;
    vec3 diffuse1 = light.diffuse * diff1 * texColor;
    vec3 specular1 = light.specular * spec1 * material.specular;

    // Atenuación Luz 1
    float dist1 = length(light.position - FragPos);
    float att1 = 1.0 / (1.0 + 0.09 * dist1 + 0.032 * dist1 * dist1);
    ambient1 *= att1;
    diffuse1 *= att1;
    specular1 *= att1;

    // --- Segunda luz ---
    vec3 lightDir2 = normalize(light2.position - FragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 reflectDir2 = reflect(-lightDir2, norm);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), material.shininess);

    vec3 ambient2 = light2.ambient * texColor;
    vec3 diffuse2 = light2.diffuse * diff2 * texColor;
    vec3 specular2 = light2.specular * spec2 * material.specular;

    // Atenuación Luz 2
    float dist2 = length(light2.position - FragPos);
    float att2 = 1.0 / (1.0 + 0.09 * dist2 + 0.032 * dist2 * dist2);
    ambient2 *= att2;
    diffuse2 *= att2;
    specular2 *= att2;

    // Sumar los resultados
    vec3 result = ambient1 + diffuse1 + specular1 + ambient2 + diffuse2 + specular2;
    color = vec4(result, 1.0);
}

