#version 330 core

out uvec4 FragColor;

uniform uint u_EntityID;

void main() { FragColor = uvec4(u_EntityID, 0, 0, 1); }
