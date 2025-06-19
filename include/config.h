#ifndef CONFIG_H
#define CONFIG_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// WINDOW
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// PLAYER
const float PLAYER_VELOCITY = 300.0f;
const glm::vec2 PLAYER_SIZE(64.0f, 64.0f);
const float ROTATE_SPEED = 90.0f;  // grades/second
const float MAX_ROTATE = 50.0f;  // maximum angle permitted for rotation

// PROJECTILE COFFEE BEAN
const float PROJECTILE_RADIUS = 9.5f;
const float PROJECTILE_SPEED = -400.0f;
const glm::vec2 INITIAL_PROJECTILE_VELOCITY(100.0f, -100.0f);
const float SHOOT_COOLDOWN = 0.5f;
const int SHOT_MAXIMUM_XVELOCITY = 75.0f;
const float MAX_OFFSET_DEGREES = 10.0f;  // beans go in a cone of 20degres

// PARTICLES
const float PARTICLE_DROP_CHANCE = 40.0f;  // 40% chance

// TEXTURES
const char* const TEXTURE_FACE = "assets/awesomeface.png";
const char* const TEXTURE_BACKGROUND = "assets/background01.png";
const char* const TEXTURE_BLOCK = "assets/coffee_block02.png";
const char* const TEXTURE_BLOCK_SOLID = "assets/coffee_block_solid01.png";
const char* const TEXTURE_SPACESHIP = "assets/spaceship01.png";
const char* const TEXTURE_COFFEE_BEAN = "assets/coffee_bean01.png";
const char* const TEXTURE_BREAK = "assets/break_block01.png";
const char* const TEXTURE_PARTICLE_SHEET = "assets/particle_sheet02.png";

// SHADERS
const char* const SHADER_VERTEX = "shaders/shader.vs";
const char* const SHADER_FRAGMENT = "shaders/shader.fs";

// LEVELS
const char* const LEVEL_ONE = "levels/one.lvl";
const char* const LEVEL_TWO = "levels/two.lvl";

// COLORS
const glm::vec3 COLOR_WHITE(1.0f);

#endif
