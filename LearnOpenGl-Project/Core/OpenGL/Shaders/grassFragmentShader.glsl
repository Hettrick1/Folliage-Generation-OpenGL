#version 330 core

in vec3 FragPos;

out vec4 FragColor;

void main()
{
    float t = clamp(FragPos.z, 0.0, 1.0);

    vec3 darkGreen = vec3(0.0, 0.4, 0.0); 
    vec3 yellow = vec3(0.8, 0.8, 0.0);

    vec3 color = mix(darkGreen, yellow, t);

    FragColor = vec4(color, 1.0);
}