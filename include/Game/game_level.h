#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "game_object.h"
#include "../Engine/sprite_renderer.h"

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class GameLevel {
public:
    // state
    std::vector<GameObject> Bricks;

    GameLevel() { }
    void load(const char* file, GLuint levelWidth, GLuint levelHeight);
    void draw(SpriteRenderer &renderer);
    bool isCompleted(); // check if the level is completed
private:
    void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif