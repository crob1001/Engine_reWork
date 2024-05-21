#ifndef OBJECT
#define OBJECT

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../texture.h"
#include "../../functs/textureFuncts.h"
#include "../../shader.h"
#include "../../functs/shaderFuncts.h"
#include "../VertArray/VertArray.hpp"

class Object {
    private:
        void update();

        void updateAngle();
        
    protected:
    public:
        VertArray *VAO;
        unsigned int vertAmt;

        float scaleVar;
        float lastScale;

        glm::vec3 angleVec;
        glm::vec3 lastAngleVec;

        glm::vec3 pos;
        glm::vec3 lastpos;

        Texture* diffuseMap;
        Texture* specularMap;

        glm::mat4 model;
        
        Object(VertArray *VAO, unsigned int vertAmt, glm::vec3 pos,
            float scale = 0,
            glm::vec3 angleVec = glm::vec3(0.0, 0.0, 0.0), 
            Texture* diffuseMap = NULL, Texture* specularMap = NULL);
        ~Object();

        void rotate(glm::vec3 rotVec);
        void translate(glm::vec3 transV);
        void scale(float scale);

        void draw(Shader* shader);
};

#endif