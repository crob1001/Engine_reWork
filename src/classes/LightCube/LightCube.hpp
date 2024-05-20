#include "../Object/Object.hpp"
#include "../Lights/PointLight/PointLight.hpp"

class LightCube : public Object, public PointLight {
    public:
    LightCube(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, VertArray *VAO, glm::vec3 pos) : Object(VAO, 36, pos, .2) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
        // this->scale(.2);
    }
};