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

// TEXTURES
const char* const TEXTURE_FACE = "assets/awesomeface.png";
const char* const TEXTURE_BACKGROUND = "assets/background01.png";
const char* const TEXTURE_BLOCK = "assets/block.png";
const char* const TEXTURE_BLOCK_SOLID = "assets/block_solid.png";
const char* const TEXTURE_SPACESHIP = "assets/spaceship01.png";

// SHADERS
const char* const SHADER_VERTEX = "shaders/shader.vs";
const char* const SHADER_FRAGMENT = "shaders/shader.fs";

// LEVELS
const char* const LEVEL_ONE = "levels/one.lvl";

// COLORS
const glm::vec3 COLOR_WHITE(1.0f);

#endif
