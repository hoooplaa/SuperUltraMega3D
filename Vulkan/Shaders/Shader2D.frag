#version 450

// --- IN --- //
layout(location = 0) in vec4 inFragColor;
layout(location = 1) in vec2 inFragTexCoord;
layout(location = 2) in vec2 inTexIndexAndType;
layout(location = 3) in vec3 inFragPos;

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

// --- MAIN --- //
void main() {
    vec3 combinedLight = vec3(1.0f);

    // Finalize
    int index = int(inTexIndexAndType.x);

    if (index < 0) { outFragColor = inFragColor; }
    else { outFragColor = texture(texSampler[index], inFragTexCoord) * inFragColor; }

    outFragColor.rgb *= combinedLight;
}