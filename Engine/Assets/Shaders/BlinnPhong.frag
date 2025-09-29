#version 330 core

// Output
out vec4 FragColor;

// Uniforms
struct Material
{
    vec4 ObjectColor;
    vec3 AmbientStrength;
    vec3 DiffuseStrength;
    vec3 SpecularStrength;
    float Shininess;
};
uniform Material u_Material;
uniform vec3 u_ViewPos;
uniform vec3 u_LightPos;
uniform vec4 u_LightColor;

// Inputs
in vec3 o_FragPos;
in vec3 o_Normal;

void main()
{
    // Ambient
    vec3 ambient = u_Material.AmbientStrength * u_LightColor.rgb;

    // Diffuse
    vec3 norm = normalize(o_Normal);
    vec3 lightDir = normalize(u_LightPos - o_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(u_Material.DiffuseStrength * diff * u_LightColor.rgb);

    // Specular
    vec3 viewDir = normalize(u_ViewPos - o_FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), u_Material.Shininess);
    vec3 specular = vec3(u_Material.SpecularStrength * spec * u_LightColor.rgb);

    // Final color
    vec3 result = (ambient + diffuse + specular) * u_Material.ObjectColor.rgb;
    FragColor = vec4(result, u_Material.ObjectColor.a);
}
