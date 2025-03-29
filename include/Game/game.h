#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"

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

    Game(GLuint width, GLuint height);  // constructor
    ~Game();  // destructor

    void init();  // initialization

    // game loop
    void processInput(float dt);  // dt == delta time
    void update(float dt);
    void render();
};

#endif