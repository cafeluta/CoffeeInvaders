#include "../../include/Engine/sprite_renderer.h"
#include "../../include/Engine/resource_manager.h"

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

void SpriteRenderer::drawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, float breakAmount) {
    // break block code
    this->shader.use();
    this->shader.setFloat("breakAmount", breakAmount);
    
    // preparing the shader
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // puts the sprite in te right pos
    model = glm::scale(model, glm::vec3(size, 1.0f));

    // updating uniforms
    this->shader.setMatrix4("model", model);
    this->shader.setVector3f("spriteColor", color);

    // no animation uniform variables
    shader.setFloat("frame", 0.0f);
    shader.setFloat("framesPerRow", 1.0f);
    shader.setFloat("frameSize", 1.0f);
    shader.setFloat("frameRows", 1.0f);

    // activating the texture we want to use for this sprite
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    this->shader.setInteger("image", 0);
    
    // block texture
    glActiveTexture(GL_TEXTURE1);
    ResourceManager::getTexture2D("break_block").bind();
    this->shader.setInteger("breakTexture", 1);

    // OpenGl now knows to map the triangles based on the given vertices in initRenderData to the given texture
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // reset to texture 0 (the sprite)
    glActiveTexture(GL_TEXTURE0);
}

void SpriteRenderer::drawSpriteAnim(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, int frame, int maxFrames) {
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    this->shader.setMatrix4("model", model);
    this->shader.setVector3f("spriteColor", color);

    this->shader.setFloat("frame", (float)frame);
    this->shader.setFloat("framesPerRow", 3.0f);
    this->shader.setFloat("frameSize", 1.0f / 3.0f);
    this->shader.setFloat("frameRows", 3.0f);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    this->shader.setInteger("image", 0);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
