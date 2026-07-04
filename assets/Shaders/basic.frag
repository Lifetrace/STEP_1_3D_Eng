#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5;

    if (projCoords.z > 1.0)
        return 0.0;

    float currentDepth = projCoords.z;

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

    // PCF — мягче края тени
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float closestDepth = texture(
                    shadowMap,
                    projCoords.xy + vec2(x, y) * texelSize
                ).r;

            shadow += currentDepth - bias > closestDepth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;

    return shadow;
}

void main()
{
    vec3 color = vec3(1.0, 0.5, 0.3);

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 ambient = 0.2 * color;
    vec3 diffuse = diff * color;

    float shadow = ShadowCalculation(FragPosLightSpace, normal, lightDir);

    vec3 result = ambient + (1.0 - shadow) * diffuse;

    FragColor = vec4(result, 1.0);
}
