#version 450

layout(std140, binding = 0) uniform UniformBufferObjectVert {
    mat4 view;
    mat4 proj;
} ubo;

layout(std140, push_constant ) uniform constants {
    mat4 model;
    mat3 texModel;

    int textureIndex;
    int PADDING1;
    int PADDING2;

    vec4 objectColor;
} push;

// IN
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

// OUT
layout(location = 0) out vec4 outFragColor;
layout(location = 1) out vec2 outFragTexCoord;
layout(location = 2) out vec2 outTexIndexAndType;
layout(location = 3) out vec3 outFragPos;

void main() {
    gl_Position = ubo.proj * ubo.view * push.model * vec4(inPosition, 1.0);

    // Out
    outFragTexCoord = vec2(vec3(inTexCoord, 0) * push.texModel);
    outTexIndexAndType.x = push.textureIndex;

    outFragColor = inColor * push.objectColor;

    outFragPos = vec3(push.model * vec4(inPosition, 1.0)); // How do this work?
}