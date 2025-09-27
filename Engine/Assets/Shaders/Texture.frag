#version 330 core

// Output
out vec4 FragColor;

// Uniforms
uniform vec4 u_Color;
uniform sampler2D u_Texture;

// Inputs
in vec2 v_TexCoord;

// Main
void main()
{
    // Set fragment color
    FragColor = texture(u_Texture, v_TexCoord);
}