#version 330 core

// Output
out vec4 FragColor;

// Uniforms
uniform samplerCube u_Skybox;

// Inputs
in VS_OUT
{
    // Light
    vec3 GlobalPosition;
    vec3 Normal;
    vec3 CameraPosition;
    vec3 DirectionalLightDirection;
    vec3 DirectionalLightColor;

    // Shadow
    vec4 LightSpacePosition;
}
fs_in;

// Main
void main() { FragColor = vec4(fs_in.GlobalPosition, 1.0); }
