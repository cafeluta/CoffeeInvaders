#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"

class SpriteRenderer {
public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void drawSprite(Texture2D &texture, glm::vec2 position,
                    glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f), float breakAmount = 0.0f);
    void drawSpriteAnim(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, int frame, int maxFrames);
private:
    Shader shader;
    GLuint quadVAO;

    void initRenderData();
};

#endif