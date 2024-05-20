#ifndef VERTARRAY_H
#define VERTARRAY_H

#include <glad/gl.h>

class VertArray {
    private:
    protected:
    public:
        unsigned int pntr;
        VertArray();
        ~VertArray();
        void AttribPointer();
        // bool isCurrent();
        // void bind();
};

#endif