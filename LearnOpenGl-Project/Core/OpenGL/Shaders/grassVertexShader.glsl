#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_InstancePosition;
layout (location = 2) in float a_Rotation;
layout (location = 3) in float a_Strengh;
layout (location = 4) in float a_Bend;

uniform mat4 u_MVP;
uniform float u_timer;

out vec3 v_Normal;
out float v_HeightPercentage;

float hash( vec2 a )
{

    return fract( sin( a.x * 3433.8 + a.y * 3843.98 ) * 45933.8 );

}

float noise( vec2 U )
{
    vec2 id = floor(U);
    U = fract(U);
    U *= U * (3.0 - 2.0 * U);
    
    vec2 A = vec2(hash(id), hash(id + vec2(0, 1)));
    vec2 B = vec2(hash(id + vec2(1, 0)), hash(id + vec2(1, 1)));
    float C = mix(A.x, A.y, U.y);
    float D = mix(B.x, B.y, U.y);
    return mix(C, D, U.x);
}

float remap(float value, float inMin, float inMax, float outMin, float outMax)
{
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}

float easeIn(float x, float power)
{
    return pow(x, power);
}

void main()
{
    v_HeightPercentage = a_Position.z / 0.7;

    float c = cos(a_Rotation);
    float s = sin(a_Rotation);
    mat4 rotationZMatrix = mat4(
        c, -s, 0.0, 0.0,
        s,  c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    float bendRot = 0;
    if(v_HeightPercentage > 0){
        bendRot = a_Bend * 0.1 * v_HeightPercentage;
    }
    float strengh = a_Strengh;

    float windNoiseSample = noise(vec2((a_Position.x + a_InstancePosition.x) * 0.8 + u_timer, (a_Position.y + a_InstancePosition.y) * 0.8 + u_timer));
    
    float windLeanAngle = remap(windNoiseSample, -1.0, 1.0, 0.25, 1.0);
    windLeanAngle = easeIn(windLeanAngle, 7.0) * 1.75;

    bendRot += (windLeanAngle * v_HeightPercentage);

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

    vec3 normal = normalize(vec3(a_Position.x * 6, a_Position.y * 6, 1.0));

    v_Normal = mat3(rotationXMatrix) * normal;

    gl_Position = u_MVP * worldPosition;
}