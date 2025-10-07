#version 330 core

// Output
out vec4 FragColor;

// Uniforms
uniform samplerCube u_Skybox;

// Inputs
in VS_OUT
{
    vec3 GlobalPosition;
    vec3 Normal;
    vec3 CameraPosition;
}
fs_in;

struct Material
{
    vec4 Color;
    float AmbientStrength;
    float DiffuseStrength;
    float SpecularStrength;
    float Shininess;
};
uniform Material u_Material;

// Main
void main() { FragColor = u_Material.Color; }
