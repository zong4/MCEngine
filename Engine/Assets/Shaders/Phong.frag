#version 330 core

out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  

// 光照参数
uniform vec3 lightPos;   // 光源位置
uniform vec3 viewPos;    // 相机位置
uniform vec3 lightColor; // 光源颜色
uniform vec3 objectColor;// 物体颜色

void main()
{
    // 1. 环境光
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // 2. 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 3. 镜面反射
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 = 高光指数（shininess）
    vec3 specular = specularStrength * spec * lightColor;

    // 4. 合并结果
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
