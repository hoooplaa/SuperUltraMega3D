#pragma once

#define INDEX_TYPE uint32_t
#define SHADER_PATH_VERT "Shaders/vert.spv"
#define SHADER_PATH_FRAG "Shaders/fragPBR.spv"
#define SHADER_PATH_BLOOM_VERT "Shaders/vert.spv"
#define SHADER_PATH_BLOOM_FRAG "Shaders/fragPBR.spv"
#define SHADER_PATH_BLOOM_COLOR_PASS_VERT "Shaders/fragPBR.spv"
#define SHADER_PATH_BLOOM_COLOR_PASS_FRAG "Shaders/fragPBR.spv"

//#define CULL_MODE VK_CULL_MODE_BACK_BIT
#define CULL_MODE VK_CULL_MODE_NONE

#define CLEAR_COLOR 0/255.0f, 0/255.0f, 0/255.0f, 1.0f

//#define LIGHT_POS 0.0f, 0.0f, 1.0f
//#define LIGHT_COUNT 1

#define MAX_TEXTURE_COUNT 10
#define MAX_LIGHT_COUNT 99

#define MAX_BONE_INFLUENCE 10

#define MTL_BASE_DIR "Assets/Models"