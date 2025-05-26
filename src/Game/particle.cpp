#include "../../include/Game/particle.h"

Particle::Particle()
        : GameObject(), Life(0.0f), Frame(0), MaxFrames(1), FrameTime(0.0f), FrameDuration(0.1f) {

}

Particle:: Particle(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity,
    float life, int maxFrames, float frameDuration)
    : GameObject(pos, size, sprite, color, velocity), Life(life), Frame(0), MaxFrames(maxFrames), FrameTime(0.0f), FrameDuration(frameDuration) {

}

void Particle::update(float dt) {
    if (this->Life > 0.0f) {
        this->Position += this->Velocity * dt;
        this->Life -= dt;
        this->FrameTime += dt;
        if (this->FrameTime >= FrameDuration && this->MaxFrames > 1) {
            this->Frame = (this->Frame + 1) % MaxFrames;
            this->FrameTime = 0.0f;
        }
    }
}
