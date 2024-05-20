#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <glm/glm.hpp>

struct SimpleLightBase {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct SimpleDirectionalLightBase : SimpleLightBase {
    glm::vec3 direction;
};

struct LightBase : SimpleLightBase {
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLightBase : LightBase, SimpleDirectionalLightBase {
    
};

#endif