#version 450

// --- IN --- //
layout(location = 0) in vec4 inFragColor;
layout(location = 1) in vec2 inFragTexCoord;
layout(location = 2) in vec2 inTexIndexAndType;
layout(location = 3) in vec3 inFragPos;
layout(location = 4) in vec3 inNormal;

// --- OUT--- //
layout(location = 0) out vec4 outFragColor;

// --- DATA--- //
struct LightData {
    int type;

    float c;
    float l;
    float q;

    float str;
    float amb;
    float spec;

    float inCutOff;
    float outCutOff;
    float PADDING1;
    float PADDING2;

    vec3  pos;
    vec3  dir;
    uvec3 col;
};

layout(std140, binding = 1) uniform UniformBufferObjectLights {
    vec3 viewPos;
    vec3 viewDir;

    uint lightCount;

    LightData lights[99];
} uboLights;

layout(binding = 2) uniform sampler2D texSampler[10];

// --- FUNCTIONS --- //
const float PI = 3.14159265359;

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
    // Calculates how much the surface reflects at zero incidence (looking directly at it)

    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
} 
float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

// --- MAIN --- //

void main() {
    vec3 viewPos = uboLights.viewPos;

    vec3 viewToFrag = normalize(viewPos - inFragPos);

    // Calculate
    vec3 Lo = vec3(0.0f);

    for (int i = 0; i < uboLights.lightCount; i++) {
        // Setup some values
        vec3 albedo     = vec3(uboLights.lights[i].c); // vec3(0.5f);
        float metallic  = uboLights.lights[i].l; // 1.0f;
        float roughness = uboLights.lights[i].q; // 0.3f;
        float ao        = uboLights.lights[i].spec; // 0.5f;
        vec3 ambient    = vec3(uboLights.lights[i].amb) * uboLights.lights[i].col * ao;

        vec3 lightCol = uboLights.lights[i].col;
        vec3 lightPos = uboLights.lights[i].pos;

        vec3 lightToFrag = normalize(lightPos - inFragPos);
        vec3 halfway     = normalize(lightToFrag + viewToFrag);

        float distance    = length((lightPos - inFragPos);
        float attenuation = 1.0f / (distance * distance);
        vec3  radiance    = lightCol * attenuation;

        // F, D, G
        vec3 F0 = mix(vec3(0.04), albedo, metallic);
        vec3 F = FresnelSchlick(max(dot(halfway, viewToFrag), 0.0), F0); 

        float NDF = DistributionGGX(inNormal, halfway, roughness);     
        float G   = GeometrySmith(inNormal, viewToFrag, lightToFrag, roughness);

        // Cook-Torrance BRDF
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(inNormal, viewToFrag), 0.0) * max(dot(inNormal, lightToFrag), 0.0)  + 0.0001;
        vec3 specular     = numerator / denominator;

        vec3 kS = F; // Light that gets reflected
        vec3 kD = vec3(1.0) - kS; // Light that gets refracted
  
        kD *= 1.0 - metallic; // Metallic surfaces dont refracte light
  
        float NdotL = max(dot(inNormal, lightToFrag), 0.0);        
        Lo += (kD * albedo / PI + specular) * radiance * NdotL * uboLights.lights[i].str;
        Lo += ambient;
    }

    vec3 lightColor = Lo;

    lightColor = lightColor / (lightColor + vec3(1.0));
    lightColor = pow(lightColor, vec3(1.0/2.2));

    // Finalize
    int index = int(inTexIndexAndType.x);

    if (index < 0) {
        outFragColor = inFragColor;
    }
    else {
    	outFragColor = texture(texSampler[index], inFragTexCoord) * inFragColor;
    }

    outFragColor.rgb *= lightColor;
}