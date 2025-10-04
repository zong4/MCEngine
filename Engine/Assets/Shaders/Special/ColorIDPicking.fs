#version 330 core
uniform uint u_EntityID;
out uvec4 FragColor;

void main() { FragColor = uvec4(u_EntityID, 0, 0, 1); }
