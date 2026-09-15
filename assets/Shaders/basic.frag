#version 460 core

out vec4 FragColor;

in vec3 FragPos;
in vec4 VertColor;
in vec4 FragPosLightSpace;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5;

    if (
        projCoords.z > 1.0 ||
            projCoords.x < 0.0 || projCoords.x > 1.0 ||
            projCoords.y < 0.0 || projCoords.y > 1.0
    ) {
        return 0.0;
    }

    float currentDepth = projCoords.z;

    float bias = max(0.02 * (1.0 - dot(normal, lightDir)), 0.002);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

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
    vec3 color = VertColor.rgb;

    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 normal = normalize(cross(dFdx(FragPos), dFdy(FragPos)));

    if (!gl_FrontFacing) {
        normal = -normal;
    }

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 ambient = 0.25 * color;
    vec3 diffuse = diff * color;

    float shadow = ShadowCalculation(FragPosLightSpace, normal, lightDir);
    vec3 result = ambient + (1.0 - shadow) * diffuse;

    FragColor = vec4(result, VertColor.a);
}
