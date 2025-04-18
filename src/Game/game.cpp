#include "../../include/Game/game.h"
#include "../../include/Engine/sprite_renderer.h"
#include "../../include/Engine/resource_manager.h"

#include <GLFW/glfw3.h>

const glm::vec2 PLAYER_SIZE(64.0f, 64.0f);
const float PLAYER_VELOCITY(300.0f);

SpriteRenderer* Renderer;
GameObject* Player;

Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

void Game::init() {
    // load shaders
    ResourceManager::loadShader("shaders/shader.vs", "shaders/shader.fs", nullptr, "sprite");

    // load the player texture
    ResourceManager::loadTexture2D("assets/spaceship01.png", true, "spaceship");

    // load the background
    ResourceManager::loadTexture2D("assets/background01.png", true, "background");

    // load the blocks
    ResourceManager::loadTexture2D("assets/block.png", false, "block");
    ResourceManager::loadTexture2D("assets/block_solid.png", false, "block_solid");

    // load the levels
    GameLevel one; one.load("levels/one.lvl", this->Width, this->Height / 2);
    // add more later

    this->Levels.push_back(one);
    this->Level = 0;

    glm::mat4 projection = glm::ortho(0.0f, (float)(this->Width), (float)(this->Height), 0.0f, -1.0f, 1.0f);  // we normalize the coords
    
    // setting the image as the active texture
    ResourceManager::getShader("sprite").use().setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);

    // render controls
    Renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));  // we need a shader to initialize a new sprite

    // player
    glm::vec2 playerPosition = glm::vec2(
        this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
        this->Height - PLAYER_SIZE.y
    );
    Player = new GameObject(playerPosition, PLAYER_SIZE, ResourceManager::getTexture2D("spaceship"));
}

void Game::update(float dt) {

}

void Game::processInput(float dt) {
    if (this->State == GAME_ACTIVE) {
        float velocity = PLAYER_VELOCITY * dt;
        if (this->Keys[GLFW_KEY_D]) {
            if (Player->Position.x  + velocity <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
        if (this->Keys[GLFW_KEY_A]) {
            if (Player->Position.x - velocity >= 0.0f)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_W]) {
            if (Player->Position.y - velocity >= 0.0f)
                Player->Position.y -= velocity;
        }
        if (this->Keys[GLFW_KEY_S]) {
            if (Player->Position.y + velocity <= this->Height - Player->Size.y)
                Player->Position.y += velocity;
        }
    }
}

void Game::render() {
    if (this->State == GAME_ACTIVE) {
        // render the background
        Renderer->drawSprite(ResourceManager::getTexture2D("background"), glm::vec2(0.0f, 0.0f), glm::vec2(640.0f, 480.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        // render the level blocks
        this->Levels[this->Level].draw(*Renderer);

        // render the spaceship sprite
        Player->draw(*Renderer);
    }
}

void Game::shutdown() {
    delete Renderer;
}