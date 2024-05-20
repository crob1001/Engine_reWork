#ifndef VERTBUFFER_H
#define VERTBUFFER_H

#include <glad/gl.h>

class VertBuffer {
    private:
    protected:
    public:
        unsigned int pntr;
        VertBuffer();
        ~VertBuffer();
        void BufferData(float vertices[]);
        void BufferData();
        // bool isCurrent();
        // void bind();
};

#endif    