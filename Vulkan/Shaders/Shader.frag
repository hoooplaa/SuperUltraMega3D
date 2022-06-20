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

// --- MAIN --- //
void main() {
    vec3 combinedLight = vec3(0.0f);

    // Constants
    float shininess = 1.0f;

    // Calculate a color for each light source and add to combined light
    for (uint i = 0; i < uboLights.lightCount; i++) {
	// Directional
        if (uboLights.lights[i].type == 0) {
	    vec3 lightDir = normalize(-uboLights.lights[i].dir);

	    // Diffuse
	    float diff = max(dot(inNormal, lightDir), 0.0);
	    // Specular
            vec3 reflectDir = reflect(-lightDir, inNormal);
	    float spec = pow(max(dot(uboLights.viewDir, reflectDir), 0.0), shininess);

	    // Combine results
            float a = uboLights.lights[i].amb;
    	    float d = diff;
    	    float s = uboLights.lights[i].spec * spec;

            combinedLight += (a + d + s) * uboLights.lights[i].col * uboLights.lights[i].str;
	 }

	// Point
	if (uboLights.lights[i].type == 1) {
	    vec3 lightDir = normalize(uboLights.lights[i].pos - inFragPos);

	    // Diffuse
    	    float diff = max(dot(inNormal, lightDir), 0.0);
	    // Specular
    	    vec3 reflectDir = reflect(-lightDir, inNormal);
    	    float spec = pow(max(dot(uboLights.viewDir, reflectDir), 0.0), shininess);
            // Attenuation
            float distance    = length(uboLights.lights[i].pos - inFragPos);
            float attenuation = 1.0 / (uboLights.lights[i].c + uboLights.lights[i].l * distance + 
  	                        uboLights.lights[i].q * (distance * distance)); 
            // Combine results
            float a = uboLights.lights[i].amb;
    	    float d = diff;
    	    float s = uboLights.lights[i].spec * spec;

	    combinedLight += (a + d + s)  * attenuation;
	}

	// Spotlight
	if (uboLights.lights[i].type == 2) {
	    vec3 lightDir = normalize(uboLights.lights[i].pos - inFragPos);
	    float theta = dot(lightDir, normalize(-uboLights.lights[i].dir));
	    
	    if (theta > uboLights.lights[i].outCutOff) { // OpenGl tutorial did the opposite
		// Fading
		float fade = uboLights.lights[i].inCutOff - uboLights.lights[i].outCutOff;
		float intensity = clamp((theta - uboLights.lights[i].outCutOff) / fade, 0.0, 1.0);  

		// Deffuse
	        float diff = max(dot(inNormal, lightDir), 0.0);

		// Specular
                vec3 reflectDir = reflect(-lightDir, inNormal);
	        float spec = pow(max(dot(uboLights.viewDir, reflectDir), 0.0), shininess);
		
		// Combine results
		float d = diff;
		float s = uboLights.lights[i].spec * spec;

		combinedLight += (d + s) * uboLights.lights[i].col * intensity;
	    }
	    
	    // Add ambient light
	    //combinedLight += uboLights.lights[i].amb;
	}
	
	// Add color and strength
	combinedLight = combinedLight * uboLights.lights[i].col * uboLights.lights[i].str;
    }

    // Finalize
    int index = int(inTexIndexAndType.x);

    if (index < 0) {
        outFragColor = inFragColor;
    }
    else {
    	outFragColor = texture(texSampler[index], inFragTexCoord) * inFragColor;
    }

    outFragColor.rgb *= combinedLight;
}