# version 330 core

// STRUCTS
struct Light {
    vec3 origin;
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    bool isPoint;
};

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    vec3 emission;
    float shiny;
};


// SHADER I/O
in vec3 fragNormalView;
in vec3 fragPosView;

out vec4 fragColor;


// UNIFORMS
uniform mat4 view;
uniform Material material;

const int MAX_LIGHTS = 64;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];


void main() {
    // Eye at (0, 0, 0) in view space
    vec3 viewDir = normalize(-fragPosView);
    vec3 normal = normalize(fragNormalView);

    vec3 illumination = material.ambient + material.emission;
    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (i > numLights) { break; }
        Light light = lights[i];
        vec3 lightDir;
        if (light.isPoint) {
            // Point light
            vec4 lightOriginViewH = view * vec4(light.origin, 1.0);
            vec3 lightOriginView = lightOriginViewH.xyz / lightOriginViewH.w;
            lightDir = normalize(lightOriginView - fragPosView);
        } else {
            // Directional light
            lightDir = normalize(light.origin);
        }
        // Diffuse
        vec3 intensity_d = light.diffuse * max(0., dot(lightDir, normal));
        vec3 illumination_d = intensity_d * material.diffuse;

        // Specular
        vec3 halfVec = normalize(lightDir + viewDir);
        vec3 intensity_s = light.specular * pow(max(0., dot(halfVec, normal)), material.shiny);
        vec3 illumination_s = intensity_s * material.specular;

        illumination += illumination_d + illumination_s;
    }
    fragColor = vec4(illumination, 1.0f);
}

