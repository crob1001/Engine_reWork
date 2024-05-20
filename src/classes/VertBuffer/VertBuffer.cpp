#include "VertBuffer.hpp"

 VertBuffer::VertBuffer() {
    glGenBuffers(1, &pntr);
}

 VertBuffer::~VertBuffer(){
    glDeleteBuffers(1, &pntr);
}

void  VertBuffer::BufferData(float vertices[]) {
    glBindBuffer(GL_ARRAY_BUFFER, pntr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void  VertBuffer::BufferData() {
    float vertices[] = {
            0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  0.0,  1.0,
            -0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  1.0,  0.0,
            -0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  1.0,  1.0,
            0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  0.0,  0.0,
            -0.5,  0.5, -0.5,  0.0,  0.0, -1.0,  1.0,  0.0,
            0.5, -0.5, -0.5,  0.0,  0.0, -1.0,  0.0,  1.0,

            -0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  0.0,  1.0,
            0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  1.0,  0.0,
            0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  1.0,  1.0,
            -0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  0.0,  0.0,
            0.5,  0.5,  0.5,  0.0,  0.0,  1.0,  1.0,  0.0,
            -0.5, -0.5,  0.5,  0.0,  0.0,  1.0,  0.0,  1.0,

            -0.5,  0.5,  0.5, -1.0,  0.0,  0.0,  1.0,  0.0,
            -0.5, -0.5, -0.5, -1.0,  0.0,  0.0,  0.0,  1.0,
            -0.5,  0.5, -0.5, -1.0,  0.0,  0.0,  1.0,  1.0,
            -0.5, -0.5, -0.5, -1.0,  0.0,  0.0,  0.0,  1.0,
            -0.5,  0.5,  0.5, -1.0,  0.0,  0.0,  1.0,  0.0,
            -0.5, -0.5,  0.5, -1.0,  0.0,  0.0,  0.0,  0.0,

            0.5,  0.5,  0.5,  1.0,  0.0,  0.0,  1.0,  0.0,
            0.5,  0.5, -0.5,  1.0,  0.0,  0.0,  1.0,  1.0,
            0.5, -0.5, -0.5,  1.0,  0.0,  0.0,  0.0,  1.0,
            0.5, -0.5, -0.5,  1.0,  0.0,  0.0,  0.0,  1.0,
            0.5, -0.5,  0.5,  1.0,  0.0,  0.0,  0.0,  0.0,
            0.5,  0.5,  0.5,  1.0,  0.0,  0.0,  1.0,  0.0,

            -0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  0.0,  1.0,
            0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  1.0,  0.0,
            0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  1.0,  1.0,
            0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  1.0,  0.0,
            -0.5, -0.5, -0.5,  0.0, -1.0,  0.0,  0.0,  1.0,
            -0.5, -0.5,  0.5,  0.0, -1.0,  0.0,  0.0,  0.0,

            -0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  0.0,  1.0,
            0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  1.0,  1.0,
            0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  1.0,  0.0,
            0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  1.0,  0.0,
            -0.5,  0.5,  0.5,  0.0,  1.0,  0.0,  0.0,  0.0,
            -0.5,  0.5, -0.5,  0.0,  1.0,  0.0,  0.0,  1.0 
    };
    glBindBuffer(GL_ARRAY_BUFFER, pntr);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

// bool  VertBuffer::isCurrent() {
//     if (*currentVBO == this->pntr) {
//         return true;
//     } else return false;
// }

// void  VertBuffer::bind() {
//     if (!this->isCurrent()) {
//         glBindBuffer(GL_ARRAY_BUFFER, this->pntr);
//     }
// }