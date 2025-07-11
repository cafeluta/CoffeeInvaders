#include "../../include/Game/game.h"
#include "../../include/Engine/sprite_renderer.h"
#include "../../include/Engine/resource_manager.h"
#include "../../include/Game/projectile_object.h"
#include "../../include/Game/particle.h"
#include "../../include/config.h"

#include <algorithm>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

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
    ResourceManager::loadShader(TEXT_VERTEX, TEXT_FRAGMENT, nullptr, "text_shader");
    Shader& textShader = ResourceManager::getShader("text_shader");
    glm::mat4 projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    textShader.use();
    textShader.setMatrix4("projection", projection);
    textShader.setInteger("text", 0);
    // Shader& s = ResourceManager::getShader("text_shader");
    // std::cout << "Text shader ID = " << s.id << std::endl;

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
    GameLevel two; two.load(LEVEL_TWO, this->Width, this->Height / 2);
    // add more later

    // load text
    ResourceManager::loadText(SCR_WIDTH , SCR_HEIGHT, "default");

    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Level = 0;

    // projection = glm::ortho(0.0f, (float)(this->Width), 0.0f, (float)(this->Height), -1.0f, 1.0f);  // we normalize the coords
    
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

    // debug purpose
    this->State = GAME_TRANSITION;
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

    if (this->checkIfLevelIsCompleted()) {
        if (this->Level + 1 < this->Levels.size()) {
            // this->Level++;
            this->State = GAME_TRANSITION;  // continue screen

            // reset game objects
            // Beans.clear();
            // Particles.clear();
            // Player->Position = glm::vec2(this->Width / 2.0f - Player->Size.x / 2.0f, this->Height - Player->Size.y );
        } else {
            // TODO !! update game state still no case for this one but will implement it later
            this->State = GAME_WIN;
        }
    }
}

void Game::processInput(float dt) {
    if (this->State == GAME_ACTIVE) {
        float velocity = PLAYER_VELOCITY * dt;
        glm::vec2 oldPosition = Player->Position;
        if (this->Keys[GLFW_KEY_D]) {
            if (Player->Position.x  + velocity <= this->Width - Player->Size.x) {
                Player->Position.x += velocity;

                if (checkCollisionPlayerBlock())
                    Player->Position = oldPosition;
            }
        }
        if (this->Keys[GLFW_KEY_A]) {
            if (Player->Position.x - velocity >= 0.0f) {
                Player->Position.x -= velocity;

                if (checkCollisionPlayerBlock())
                    Player->Position = oldPosition;
            }
        }
        if (this->Keys[GLFW_KEY_W]) {
            if (Player->Position.y - velocity >= 0.0f) {
                Player->Position.y -= velocity;

                if (checkCollisionPlayerBlock())
                    Player->Position = oldPosition;
            }
        }
        if (this->Keys[GLFW_KEY_S]) {
            if (Player->Position.y + velocity <= this->Height - Player->Size.y) {
                Player->Position.y += velocity;

                if (checkCollisionPlayerBlock())
                    Player->Position = oldPosition;
            }
        }

        // don't shoot like a machine gun please!
        float currentTime = glfwGetTime();

        if (this->Keys[GLFW_KEY_SPACE] && currentTime - lastShotTime >= SHOOT_COOLDOWN) {
            this->KeysProcessed[GLFW_KEY_SPACE] = true;

            // the angle is adjusted +90.0f cuz i'm lazy to modify the logic of the rotation now
            // the spaceship in centered with the fron on 0degrees left is <0 and right is > 0
            float baseAngle = glm::radians(Player->Rotation + 90.0f);  

            // 10degrees variation
            float angleOffset = ((float)(rand() % 1001) / 1000.0f) * 2.0f * MAX_OFFSET_DEGREES - MAX_OFFSET_DEGREES;
            float finalAngle = baseAngle + glm::radians(angleOffset);

            glm::vec2 direction(cos(finalAngle), sin(finalAngle));
            direction = glm::normalize(direction);

            // updated position so the bean spawns from the front of the ship
            glm::vec2 beanPos = Player->Position + Player->Size * 0.5f - glm::vec2(PROJECTILE_RADIUS);
            
            glm::vec2 beanVelocity = direction * PROJECTILE_SPEED;

            ProjectileObject newBean(beanPos, PROJECTILE_RADIUS, beanVelocity, ResourceManager::getTexture2D("bean"));
            newBean.Stuck = false;
            Beans.push_back(newBean);

            lastShotTime = currentTime;
        }


        // spaceship rotation
        if (this->Keys[GLFW_KEY_LEFT]) {
            Player->Rotation -= ROTATE_SPEED * dt;
            if (Player->Rotation < -MAX_ROTATE)
                Player->Rotation = -MAX_ROTATE;
        }
        if (this->Keys[GLFW_KEY_RIGHT]) {
            Player->Rotation += ROTATE_SPEED * dt;
            if (Player->Rotation > MAX_ROTATE)
                Player->Rotation = MAX_ROTATE;
        }
        // reset rotation on arrow key up
        if (this->Keys[GLFW_KEY_UP]) {
            Player->Rotation = 0.0f;
        }
    }

    if (this->State == GAME_TRANSITION) {
        if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER]) {
            // update the enter key
            this->KeysProcessed[GLFW_KEY_ENTER] = true;

            // load new level
            this->Level++;

            // reset level entities
            Beans.clear();
            Particles.clear();
            Player->Position = glm::vec2(this->Width / 2.0f - Player->Size.x / 2.0f, this->Height - Player->Size.y );
            this->State = GAME_ACTIVE;
        }
        return;
    }
}

void Game::render() {
    if (this->State == GAME_ACTIVE) {
        ResourceManager::getShader("sprite").use(); 
        // render the background
        Renderer->drawSprite(ResourceManager::getTexture2D("background"), glm::vec2(0.0f, 0.0f), glm::vec2(SCR_WIDTH, SCR_HEIGHT), 0.0f, COLOR_WHITE);

        // render the level blocks
        this->Levels[this->Level].draw(*Renderer);

        // render the spaceship sprite
        float angle = glm::radians(Player->Rotation);  // convert to radians
        Player->draw(*Renderer, 0.0f, Player->Rotation);

        // render multiple beans
        for (ProjectileObject &bean : Beans)
            bean.draw(*Renderer);

        // render particles
        for (Particle& p : Particles) {
            Renderer->drawSpriteAnim(p.Sprite, p.Position, p.Size, p.Rotation, p.Color, p.Frame, p.MaxFrames);
        }
    }
    
    if (this->State == GAME_TRANSITION) {
        Renderer->drawSprite(ResourceManager::getTexture2D("background"), glm::vec2(0.0f, 0.0f), glm::vec2(SCR_WIDTH, SCR_HEIGHT), 0.0f, COLOR_WHITE);

        // draw text later
        ResourceManager::getShader("text_shader").use();

        char congrats[100];
        sprintf(congrats, "WP, Level %d Done!", this->Level + 1);
        
        ResourceManager::getText("default").render(ResourceManager::getShader("text_shader"), congrats, 220.0f, 200.0f, 1.0f, COLOR_WHITE);
        ResourceManager::getText("default").render(ResourceManager::getShader("text_shader"), "PRESS ENTER TO CONTINUE", 150.0f, 300.0f, 0.8f, COLOR_WHITE);
        return;
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
                    } else {  // block is undestructable
                        // ricochete beans
                        bean.Velocity.y = -bean.Velocity.y;

                        // move the bean a bit above or a a bit below the block
                        if (bean.Velocity.y > 0) {
                            bean.Position.y = bean.Position.y + bean.Size.y + 0.1f;
                        } else {
                            bean.Position.y = bean.Position.y - bean.Size.y - 0.1f;
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

bool Game::checkIfLevelIsCompleted() {
    for (auto& brick : this->Levels[this->Level].Bricks)
        if (!brick.IsSolid && !brick.IsDestroyed)
            return false;
    return true;
}

bool Game::checkCollisionPlayerBlock() {
    for (auto& box : this->Levels[this->Level].Bricks) {
        if (checkCollisionProjGameObject(*Player, box))
            return true;
    }
    return false;
}

void Game::shutdown() {
    delete Renderer;
}

// TODO implement the rotation of the spaceship on arrow keys