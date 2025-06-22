#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Text {
public:
    Text();  // fml we need a default constructor
    Text(GLuint width, GLuint height);
    void render(std::string text, float x, float y, float scale, glm::vec3 color);
private:
    GLuint VAO, VBO;
    GLuint screenWidth, screenHeight;
};

#endif