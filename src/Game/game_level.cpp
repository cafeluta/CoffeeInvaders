#include "../../include/Game/game_level.h"
#include "../../include/Engine/resource_manager.h"
#include "../../include/Engine/sprite_renderer.h"
#include "../../include/config.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

void GameLevel::load(const char* file, GLuint levelWidth, GLuint levelHeight) {
    this->Bricks.clear();
    GLuint tileCode;
    GameLevel level;
    
    std::string buffer;  // used for reading lines from file
    std::ifstream fstream(file);  // stream of data from file
    std::vector<std::vector<GLuint>> tileData;  // matrix with tile codes

    if (fstream) {  // if the file exists
        while (std::getline(fstream, buffer)) {
            std::istringstream sstream(buffer);  // string stream
            std::vector<GLuint> row;

            // reading values from file matrix of codes inside tileData
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }

        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    } else {
        std::cout << "| ERROR:: GameLevel file at: " << file << " doesn't exists!" 
                << "\n -- --------------------------------------------------- -- "
                << std::endl;
    }
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight) {
    GLuint height = tileData.size();  // num of rows
    GLuint width = tileData[0].size();  // num of cols

    float unitWidth = levelWidth / (float)width;
    float unitHeight = levelHeight / height;  // watch out here for errors

    // initialize level tiles
    for (GLuint y = 0; y < height; y++) {
        for (GLuint x = 0; x < width; x++) {
            if (tileData[y][x] == 1) {  // solid obj
                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                GameObject obj(pos, size, ResourceManager::getTexture2D("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = true;
                this->Bricks.push_back(obj);
            } else {
                int code = tileData[y][x];
                float darken = 1.0f - 0.18f * (code - 2);  // making it darker and darker

                if (darken < 0.2f) darken = 0.3f;  // not too dark now :))

                glm::vec3 color = glm::vec3(darken);

                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                this->Bricks.push_back(GameObject(pos, size, ResourceManager::getTexture2D("block"), color));
            }
        }
    }
}

void GameLevel::draw(SpriteRenderer &renderer) {
    for (GameObject &tile : this->Bricks)
        if (!tile.IsDestroyed)
            tile.draw(renderer);
}

bool GameLevel::isCompleted() {
    for (GameObject &tile : this->Bricks)
        if (!tile.IsSolid && !tile.IsDestroyed)
            return false;
    return true;
}
