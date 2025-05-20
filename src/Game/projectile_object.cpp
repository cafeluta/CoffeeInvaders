#include "../../include/Game/projectile_object.h"

ProjectileObject::ProjectileObject() 
    : GameObject(), Radius(12.5f), Stuck(true) { }

ProjectileObject::ProjectileObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity, 1), Radius(radius), Stuck(true) { }

glm::vec2 ProjectileObject::move(float dt, GLuint windowWidth) {
    if (!this->Stuck) {
        this->Position += this->Velocity * dt;
        
        if (this->Position.x <= 0.0f) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        } else if (this->Position.x + this->Size.x >= windowWidth) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = windowWidth - this->Size.x;
        }
        if (this->Position.y <= 0.0f) {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
    return this->Position;
}

void ProjectileObject::reset(glm::vec2 position, glm::vec2 velocity) {
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}