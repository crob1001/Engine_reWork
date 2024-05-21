#ifndef TEXTFUNCT
#define TEXTFUNCT
#include <glad/gl.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "../stb_image.h"
#include "../texture.h"

Texture createTexture(const char *path, bool trans) {

    Texture tex;

    glGenTextures(1, &tex.texture);

    // int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &tex.width, &tex.height, &tex.nrComponents, 0);
    if (data) {
        GLenum format;

        switch(tex.nrComponents) {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
        }

        glBindTexture(GL_TEXTURE_2D, tex.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, tex.width, tex.height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

    }
    else {
        printf("Texture failed to load at path: ");
        stbi_image_free(data);
    }

    return tex;
}

#endif