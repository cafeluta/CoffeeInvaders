#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../Engine/texture.h"
#include "../Engine/sprite_renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject {
public:
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    float Rotation;
    bool IsSolid;
    bool IsDestroyed;
    int HP;  // healthpoints
    int MaxHp;
    Texture2D Sprite;  // the image that represents the sprite

    GameObject();  // empty constructor
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), int hp = -1);  // personalized constructor

    virtual void draw(SpriteRenderer &renderer, float breakAmount = 0.0f);  // virtual void so we can override this function in other classes
};

#endif
