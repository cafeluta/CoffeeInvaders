#include "../../include/Engine/sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    if (glIsVertexArray(this->quadVAO))
        glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData() {
    GLuint VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::drawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    // preparing the shader
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // puts the sprite in te right pos

    // rotating the sprite around its center
    // model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));  // temporarily going to the center of the sprite
    // model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    // model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));  // going back

    model = glm::scale(model, glm::vec3(size, 1.0f));

    // updating uniforms
    this->shader.setMatrix4("model", model);
    this->shader.setVector3f("spriteColor", color);

    // activating the texture we want to use for this sprite
    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    // OpenGl now knows to map the triangles based on the given vertices in initRenderData to the given texture
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
