#ifndef TEXTURE
#define TEXTURE

struct Texture_s {
    int width, height, nrComponents;
    unsigned int texture;
    unsigned int pixels[];
};

typedef struct Texture_s Texture;
#endif 
