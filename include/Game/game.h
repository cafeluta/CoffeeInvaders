#ifndef GAME_H
#define GAME_H

#include "game_level.h"

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public: 
    GameState State;
    bool Keys[1024];  // using this for inputs
    GLuint Width, Height;

    // newly added (levels)
    std::vector<GameLevel> Levels;
    GLuint Level;

    Game(GLuint width, GLuint height);  // constructor
    // ~Game();  // destructor

    void init();  // initialization

    // game loop
    void processInput(float dt);  // dt == delta time
    void update(float dt);
    void render();

    void shutdown();
};

#endif