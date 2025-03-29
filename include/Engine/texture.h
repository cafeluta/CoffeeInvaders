#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D {
public:
    GLuint id;
    GLuint Width, Height;  // of the loaded image
    GLuint InternalFormat;  // format of texture obj
    GLuint ImageFormat;
    GLuint WrapS, WrapT;
    GLuint FilterMin, FilterMax;
    Texture2D();  // constructor
    void generate(GLuint width, GLuint height, unsigned char* data);  // generates texture from loaded image
    void bind() const;  // binds the curr GL_TEXTURE_2D obj to this texture
};

#endif