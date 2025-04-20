#ifndef PROJECTILE_OBJECT_H
#define PROJECTILE_OBJECT_H

#include "game_object.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ProjectileObject : public GameObject {
public:
    float Radius;
    bool Stuck;

    ProjectileObject();
    ProjectileObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

    glm::vec2 move(float dt, GLuint windowWidth);
    void reset(glm::vec2 position, glm::vec2 velocity);
    void erase();
};

#endif