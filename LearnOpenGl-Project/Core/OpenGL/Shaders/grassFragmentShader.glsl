#version 330 core

in float v_HeightPercentage;
in vec3 v_Normal;

uniform vec3 u_LightDirection;
uniform vec3 u_LightColor;
uniform vec3 u_AmbientColor;

out vec4 FragColor;

void main()
{
    float t = clamp(v_HeightPercentage * 0.8, 0.0, 1.0);
    vec3 darkGreen = vec3(0.0, 0.5, 0.0); 
    vec3 yellow = vec3(0.7, 0.7, 0.0);
    vec3 baseColor = mix(darkGreen, yellow, t);

    vec3 normal = normalize(v_Normal);
    vec3 lightDir = normalize(-u_LightDirection);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;

    float fresnel = pow(1.0 - max(dot(normal, lightDir), 0.0), 2.0);
    vec3 fresnelEffect = mix(vec3(0.0, 0.3, 0.1), u_LightColor, fresnel);
    diffuse += fresnelEffect * 0.1;

    vec3 ambient = u_AmbientColor * 1.4;

    vec3 finalColor = (ambient + diffuse) * baseColor;

    FragColor = vec4(finalColor, 1.0);
}