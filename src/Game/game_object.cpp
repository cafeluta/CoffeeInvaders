#include "../../include/Game/game_object.h"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), IsDestroyed(false), HP(-1), MaxHp(-1){
    
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity, int hp)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), IsDestroyed(false), HP(hp), MaxHp(hp){
    
}

void GameObject::draw(SpriteRenderer &renderer, float breakAmount) {
    renderer.drawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color, breakAmount);
}