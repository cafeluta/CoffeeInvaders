#include "../../include/Game/game.h"
#include "../../include/Engine/sprite_renderer.h"
#include "../../include/Engine/resource_manager.h"

SpriteRenderer* Renderer;

Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

void Game::init() {
    // load shaders
    ResourceManager::loadShader("shaders/shader.vs", "shaders/shader.fs", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, (float)(this->Width), (float)(this->Height), 0.0f, -1.0f, 1.0f);  // we normalize the coords
    ResourceManager::getShader("sprite").use().setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);

    // render controls
    Shader myShader;
    myShader = ResourceManager::getShader("sprite");
    Renderer = new SpriteRenderer(myShader);
    ResourceManager::loadTexture2D("assets/awesomeface.png", true, "face");
}

void Game::update(float dt) {

}

void Game::processInput(float dt) {

}

void Game::render() {
    Texture2D myTexture;
    myTexture = ResourceManager::getTexture2D("face");
    Renderer->drawSprite(myTexture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::shutdown() {
    delete Renderer;
}