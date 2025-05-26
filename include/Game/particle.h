#ifndef PARTICLE_H
#define PARTICLE_H

#include "game_object.h"

class Particle : public GameObject {
public:
    float Life;  // how many seconds on screen
    int Frame;  // curent fram for the animation
    int MaxFrames;  // frames in sprite sheet
    float FrameTime;
    float FrameDuration;

    Particle();
    Particle(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity, float life, int maxFrames = 1, float frameDuration = 0.1f);
    void update(float dt);  // update attributes
};

#endif