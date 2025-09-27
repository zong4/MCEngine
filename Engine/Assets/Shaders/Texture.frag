#version 330 core

// Output
out vec4 FragColor;

// Uniforms
uniform vec4 u_Color;

// Inputs

// Main
void main()
{
    // Set fragment color
    FragColor = u_Color;
}