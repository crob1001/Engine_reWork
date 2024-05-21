#include "Object.hpp"

Object::Object(VertArray *VAO, unsigned int vertAmt, glm::vec3 pos, float scale, glm::vec3 angleVec, Texture* diffuseMap, Texture* specularMap) {
    this->VAO = VAO;
    this->vertAmt = vertAmt;
    this->pos = pos;
    this->diffuseMap = diffuseMap;
    this->specularMap = specularMap;
    this->scaleVar = scale;

    // this->model = glm::mat4(1.0f);
    this->translate(this->pos);
    this->scale(scaleVar);
    this->angleVec = angleVec;

    this->model = glm::mat4(1.0f);
    
}

Object::~Object() {
    
}

void Object::translate(glm::vec3 pos) {
    this->pos = pos;
}

void Object::rotate(glm::vec3 angleVec) {
    this->angleVec = angleVec;
}

// void Object::rotate(float radians, glm::vec3 axisVec) {
//     // this->angle = glm::degrees(radians);
//     this->model = glm::rotate(this->model, radians, axisVec);
// }

void Object::scale(float scale) {
    this->scaleVar = scale;
}

void Object::updateAngle() {
    if (this->angleVec.x != this->lastAngleVec.x) {
            this->model = glm::rotate(this->model, this->angleVec.x, glm::vec3(1,0,0));
            this->lastAngleVec.x = this->angleVec.x;
        }
        if (this->angleVec.y != this->lastAngleVec.y) {
            this->model = glm::rotate(this->model, this->angleVec.y, glm::vec3(0,1,0));
            this->lastAngleVec.y = this->angleVec.y;
        } 
        if (this->angleVec.z != this->lastAngleVec.z) {
            this->model = glm::rotate(this->model, this->angleVec.z, glm::vec3(0,0,1));
            this->lastAngleVec.z = this->angleVec.z;
        }
}

void Object::update() {
    if (this->pos != this->lastpos) {
        this->model = glm::translate(this->model, this->pos);
        this->lastpos = this->pos;
    }
    if (this->angleVec != this->lastAngleVec) {
        updateAngle();
    }
    if (this->scaleVar != this->lastScale) {
        this->model = glm::scale(this->model, glm::vec3(scaleVar));
        this->lastScale = this->scaleVar;
    }
}

void Object::draw(Shader* shader) {
    Object::update();
    setMat4(*shader, "model", this->model);
    glDrawArrays(GL_TRIANGLES, 0, this->vertAmt);
}