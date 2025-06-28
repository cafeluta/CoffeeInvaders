#ifndef TEXT_H
#define TEXT_H

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"

// struct for characters glyph details
struct Character {
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class Text {
public:
    std::map<GLchar, Character> Characters;
    unsigned int VAO = 0, VBO = 0;

    Text() = default;
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;
    Text(Text&&) = default;
    Text& operator=(Text&&) = default;
    ~Text();

    bool load(const std::string& font, unsigned int fontSize);
    void render(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif