#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
    public:
    int width, height, nrChannels;
    unsigned int texture;

    unsigned int pixels[];
    
    Texture(const char path[], bool trans = false);

    unsigned int* getTexture();
    
};

#endif