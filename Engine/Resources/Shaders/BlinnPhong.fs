#version 330 core

struct PointLight
{
    vec3 Position;
    vec3 Color;

    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight
{
    vec3 Position;
    vec3 Direction;
    vec3 Color;

    float Constant;
    float Linear;
    float Quadratic;

    float CutOff;
    float OuterCutOff;
};

// Output
out vec4 FragColor;

// Uniforms
struct Material
{
    vec4 Color;
    float AmbientStrength;
    float DiffuseStrength;
    float SpecularStrength;
    float Shininess;
};
uniform Material u_Material;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;
uniform samplerCube u_Skybox;
uniform sampler2D u_ShadowMap;

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

// Function prototypes
vec3 CalcDirectionalLight(vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 viewDir);
float CalDiffuseFactor(vec3 lightDir, vec3 normal);
float CalSpecularFactor(vec3 lightDir, vec3 viewDir, vec3 normal, float shininess);

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    if (projCoords.z > 1.0 || projCoords.x < 0.0 || projCoords.x > 1.0 || projCoords.y < 0.0 || projCoords.y > 1.0)
        return 0.0;

    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(u_ShadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

// Main
void main()
{
    vec3 viewDir = normalize(fs_in.CameraPosition - fs_in.GlobalPosition);

    // Light
    vec3 resultLight = vec3(0.0);
    resultLight += CalcDirectionalLight(viewDir);
    resultLight += CalcPointLight(u_PointLight, viewDir);
    resultLight += CalcSpotLight(u_SpotLight, viewDir);

    // Skybox
    vec3 resultSkybox = vec3(0.0);
    // resultSkybox += texture(u_Skybox, reflect(-viewDir, normalize(fs_in.Normal))).rgb * u_Material.SpecularStrength;
    // resultSkybox += texture(u_Skybox, refract(-viewDir, normalize(fs_in.Normal), 1.00 / 1.52)).rgb * 0.5;

    vec3 result = resultLight + resultSkybox;

    // HDR tonemapping
    float exposure = 1.0;
    result = vec3(1.0) - exp(-result * exposure);

    FragColor = vec4(result, u_Material.Color.a);
}

vec3 CalcDirectionalLight(vec3 viewDir)
{
    vec3 lightDir = normalize(-fs_in.DirectionalLightDirection);
    float diff = CalDiffuseFactor(lightDir, fs_in.Normal);
    float spec = CalSpecularFactor(lightDir, viewDir, fs_in.Normal, u_Material.Shininess);

    return ((1.0 - ShadowCalculation(fs_in.LightSpacePosition)) *
            (u_Material.DiffuseStrength * diff + u_Material.SpecularStrength * spec)) *
           u_Material.Color.rgb * fs_in.DirectionalLightColor;
}

vec3 CalcPointLight(PointLight light, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - fs_in.GlobalPosition);

    float diff = CalDiffuseFactor(lightDir, fs_in.Normal);
    float spec = CalSpecularFactor(lightDir, viewDir, fs_in.Normal, u_Material.Shininess);

    // Attenuation
    float distance = length(light.Position - fs_in.GlobalPosition);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    return (u_Material.AmbientStrength * u_Material.Color.rgb +
            u_Material.DiffuseStrength * diff * u_Material.Color.rgb + u_Material.SpecularStrength * spec) *
           light.Color * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - fs_in.GlobalPosition);

    float diff = CalDiffuseFactor(lightDir, fs_in.Normal);
    float spec = CalSpecularFactor(lightDir, viewDir, fs_in.Normal, u_Material.Shininess);

    // Attenuation
    float distance = length(light.Position - fs_in.GlobalPosition);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.Direction));
    float epsilon = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);

    return (u_Material.AmbientStrength * u_Material.Color.rgb +
            u_Material.DiffuseStrength * diff * u_Material.Color.rgb + u_Material.SpecularStrength * spec) *
           light.Color * attenuation * intensity;
}

float CalDiffuseFactor(vec3 lightDir, vec3 normal) { return max(dot(normal, lightDir), 0.0); }
float CalSpecularFactor(vec3 lightDir, vec3 viewDir, vec3 normal, float shininess)
{
    vec3 halfwayDir = normalize(lightDir + viewDir);
    return pow(max(dot(normal, halfwayDir), 0.0), shininess);
}