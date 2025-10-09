#version 330 core

// Output
out uvec4 FragColor;

// Inputs
in VS_OUT
{
    flat uint EntityID;
    vec3 CameraPosition;
    vec3 Position;
    vec3 Normal;
    vec4 Color;
    vec4 Material;
}
fs_in;

void main() { FragColor = uvec4(fs_in.EntityID, 0, 0, 1); }
