#version 330 core

layout(location = 0) in vec3 aPos;      // 顶点位置
layout(location = 1) in vec3 aNormal;   // 顶点法线

out vec3 FragPos;  
out vec3 Normal;  

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    FragPos = vec3(u_Model * vec4(aPos, 1.0));              // 世界坐标
    Normal  = mat3(transpose(inverse(u_Model))) * aNormal;  // 转换到世界空间的法线

    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}
