#include "VertArray.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

 VertArray::VertArray() {
    glGenVertexArrays(1, &pntr);
}

 VertArray::~VertArray() {
    glDeleteVertexArrays(1, &this->pntr);
}

// bool VertArray::isCurrent() {
//     return true;
//     if (*currentVAO == this->pntr) {
//         return true;
//     } else return false;
// }

// void VertArray::bind() {
//     if (!this->isCurrent()) {
//         glBindVertexArray(this->pntr);
//     }
// }