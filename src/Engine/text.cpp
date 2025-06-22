#include "../../include/Engine/text.h"
#include "../../lib/stb_easy_font.h"
#include <vector>

Text::Text() : screenWidth(0), screenHeight(0) {

}

Text::Text(GLuint width, GLuint height) : screenWidth(width), screenHeight(height) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 9999 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // unbinding buffer and VAO so we don't need to debug this later
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::render(std::string text, float x, float y, float scale, glm::vec3 color) {
    char buffer[9999];
    int quads = stb_easy_font_print(x, y, (char*)text.c_str(), NULL, buffer, sizeof(buffer));

    // openGL setup
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, quads * 4 * 2 * sizeof(float), buffer);

    // shader already running
    glDrawArrays(GL_QUADS, 0, quads * 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
