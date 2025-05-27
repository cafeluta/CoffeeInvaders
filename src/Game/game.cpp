#include "../../include/Game/game.h"
#include "../../include/Engine/sprite_renderer.h"
#include "../../include/Engine/resource_manager.h"
#include "../../include/Game/projectile_object.h"
#include "../../include/Game/particle.h"
#include "../../include/config.h"

#include <algorithm>
#include <GLFW/glfw3.h>
#include <cstdlib>

SpriteRenderer* Renderer;
ProjectileObject* Player;

std::vector<ProjectileObject> Beans;
float lastShotTime = 0.0f;

std::vector<Particle> Particles;
Texture2D* ParticleTexture = nullptr;

Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), KeysProcessed(), Width(width), Height(height) {

}

void Game::init() {
    // load shaders
    ResourceManager::loadShader(SHADER_VERTEX, SHADER_FRAGMENT, nullptr, "sprite");

    // load the player texture
    ResourceManager::loadTexture2D(TEXTURE_SPACESHIP, true, "spaceship");

    // load the background
    ResourceManager::loadTexture2D(TEXTURE_BACKGROUND, true, "background");

    // load the blocks
    ResourceManager::loadTexture2D(TEXTURE_BLOCK, true, "block");
    ResourceManager::loadTexture2D(TEXTURE_BLOCK_SOLID, true, "block_solid");
    ResourceManager::loadTexture2D(TEXTURE_BREAK, true, "break_block");

    // load the coffee bean projectile
    ResourceManager::loadTexture2D(TEXTURE_COFFEE_BEAN, true, "bean");

    // load the particle spritesheet
    ResourceManager::loadTexture2D(TEXTURE_PARTICLE_SHEET, true, "particle_sheet");

    // load the levels
    GameLevel one; one.load(LEVEL_ONE, this->Width, this->Height / 2);
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
    Player = new ProjectileObject(playerPosition, 24.0f, glm::vec2(0.0f, 0.0f),  ResourceManager::getTexture2D("spaceship"));

    // bean
    this->KeysProcessed[GLFW_KEY_SPACE] = false;

    // particle
    ParticleTexture = &ResourceManager::getTexture2D("particle_sheet");
}

void Game::update(float dt) {
    for (ProjectileObject &bean : Beans)
        bean.move(dt, this->Width);

    removeProjectiles(Beans);

    this->doCollisions();
    this->removeDestroyedBricks();

    for (auto& p : Particles)
        p.update(dt);
    this->removeParticles();
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

        // don't shoot like a machine gun please!
        float currentTime = glfwGetTime();

        if (this->Keys[GLFW_KEY_SPACE] && currentTime - lastShotTime >= SHOOT_COOLDOWN){
            this->KeysProcessed[GLFW_KEY_SPACE] = true;

            glm::vec2 beanPos = Player->Position + glm::vec2(Player->Size.x / 2.0f - PROJECTILE_RADIUS, -PROJECTILE_RADIUS * 2.0f);
            glm::vec2 beanVelocity(Player->Velocity.x * 0.5f, PROJECTILE_SPEED);  // player velocity is set temporarily to 0.0f maybe in the future we can rotate the spaceship so we modify it (maybe)
            ProjectileObject newBean(beanPos, PROJECTILE_RADIUS, beanVelocity, ResourceManager::getTexture2D("bean"));
            newBean.Stuck = false;
            Beans.push_back(newBean);

            lastShotTime = currentTime;
        }
    }
}

void Game::render() {
    if (this->State == GAME_ACTIVE) {
        // render the background
        Renderer->drawSprite(ResourceManager::getTexture2D("background"), glm::vec2(0.0f, 0.0f), glm::vec2(SCR_WIDTH, SCR_HEIGHT), 0.0f, COLOR_WHITE);

        // render the level blocks
        this->Levels[this->Level].draw(*Renderer);

        // render the spaceship sprite
        Player->draw(*Renderer);

        // render multiple beans
        for (ProjectileObject &bean : Beans)
            bean.draw(*Renderer);

        // render particles
        for (Particle& p : Particles) {
            Renderer->drawSpriteAnim(p.Sprite, p.Position, p.Size, p.Rotation, p.Color, p.Frame, p.MaxFrames);
        }
    }
}

void Game::removeProjectiles(std::vector<ProjectileObject> &projectiles) {
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(), [](const ProjectileObject &p){  // lambda function to acces every projectile of the given vector
            // remove beans if they are off screen or they have no longer enough hp
            return (p.Position.y + p.Size.y < 0.0f) || (p.HP <= 0);
        }),
        projectiles.end()
    );
}

void Game::removeDestroyedBricks() {
    auto &bricks = this->Levels[this->Level].Bricks;
    bricks.erase(
        std::remove_if(bricks.begin(), bricks.end(),
            [] (const GameObject &box) { return box.IsDestroyed; }),
        bricks.end()
    );
}

void Game::removeParticles() {
    Particles.erase(
        std::remove_if(Particles.begin(), Particles.end(),
            [this](const Particle& p) {
                return (p.Position.y >= this->Height - p.Size.y) || (p.IsDestroyed);}),
        Particles.end()
    );
}

void Game::doCollisions() {
    // blocks collision with beans
    for (GameObject &box : this->Levels[this->Level].Bricks){  // every block
        if (!box.IsDestroyed){  // if the block isn't destroyed
            for (ProjectileObject &bean : Beans) {  // we test every bean that interacts with the blocks
                if (checkCollisionProjGameObject(bean, box)) {
                    if (!box.IsSolid) { // test if the block is undestructable
                        // take out hp on each hit
                        box.HP--;
                        bean.HP--;

                        // draw particles
                        // random chance on hit for particles to appear
                        if (checkForParticleDropChance()) {  // 40% chance
                            int maxFrames = 7;
                            float frameDuration = 0.20f;
                            for (int i = 0; i < 8; ++i) {
                                glm::vec2 partPos = box.Position + glm::vec2(rand() % (int)box.Size.x, rand() % (int)box.Size.y);
                                glm::vec2 partVel = glm::vec2((rand()%20-10)/10.0f, 60.0f + rand()%40); // random X, rapid pe Y
                                glm::vec3 color = glm::vec3(0.7f, 0.5f, 0.2f); // color
                                Particles.emplace_back(partPos, glm::vec2(32,32), *ParticleTexture, color, partVel, 0.7f, maxFrames, frameDuration);
                                                                // size
                            }
                        }

                        // delete the box if it has no more hp
                        if (box.HP <= 0) {
                            box.IsDestroyed = true;
                        }
                    }
                }
            }
        }
    }

    // particles collision with player
    for (Particle &p : Particles) {
        if (checkCollisionProjGameObject(*Player, p)) {
            p.IsDestroyed = true;
            printf("Player hit!\n");
        }
    }
}

bool Game::checkForParticleDropChance() {
    return rand() % 100 <= PARTICLE_DROP_CHANCE;
}

void Game::shutdown() {
    delete Renderer;
}