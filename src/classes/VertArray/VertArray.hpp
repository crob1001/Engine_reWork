#ifndef VERTARRAY_H
#define VERTARRAY_H

class VertArray {
    public:
    unsigned int pntr;
    VertArray();
    ~VertArray();
    void AttribPointer();
    bool isCurrent();
    void bind();
};

#endif