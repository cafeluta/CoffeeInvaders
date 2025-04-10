#include "../../include/Engine/texture.h"
#include <glad/glad.h>

Texture2D::Texture2D()
    : InternalFormat(GL_RGB), ImageFormat(GL_RGB), WrapS(GL_REPEAT), WrapT(GL_REPEAT), FilterMin(GL_LINEAR), FilterMax(GL_LINEAR) {
    glGenTextures(1, &this->id);
}

void Texture2D::generate(GLuint width, GLuint height, unsigned char* data) {
    this->Width = width;
    this->Height = height;

    // loading texture from image
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, width, height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // wrap and filter option
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->FilterMax);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
