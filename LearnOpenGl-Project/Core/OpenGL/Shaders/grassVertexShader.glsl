#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_InstancePosition;
layout (location = 2) in float a_Rotation;
layout (location = 3) in float a_Strengh;
layout (location = 4) in float a_Bend;

uniform mat4 u_MVP;
uniform float u_timer;

out float v_HeightPercentage; // Changer le nom pour éviter le conflit avec la variable locale

void main()
{
    v_HeightPercentage = a_Position.z / 0.7; // Stocker la hauteur AVANT toute transformation

    float c = cos(a_Rotation);
    float s = sin(a_Rotation);
    mat4 rotationZMatrix = mat4(
        c, -s, 0.0, 0.0,
        s,  c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    float bendRot = a_Bend * 0.25 * v_HeightPercentage;
    float strengh = a_Strengh * 5;
    float noiseSample = sin(u_timer + a_InstancePosition.x) * strengh;
    bendRot += noiseSample * (0.1 * v_HeightPercentage);
    bendRot = mix(-1.0, 1.0, smoothstep(-1.0, 1.0, bendRot));

    float y = cos(bendRot);
    float z = sin(bendRot);
    mat4 rotationXMatrix = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, y, -z, 0.0,
        0.0, z, y, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    vec4 rotatedPosition = rotationZMatrix * rotationXMatrix * vec4(a_Position, 1.0);
    vec4 worldPosition = vec4(a_InstancePosition, 1.0) + rotatedPosition;

    gl_Position = u_MVP * worldPosition;
}