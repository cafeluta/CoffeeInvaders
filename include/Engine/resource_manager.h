#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <memory>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"
#include "text.h"

class ResourceManager {
public:
    // storage
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, std::unique_ptr<Text>> Texts;

    // shader
    static Shader loadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name);
    static Shader& getShader(std::string name);

    // texture
    static Texture2D loadTexture2D(const char* file, bool alpha, std::string name);  // alpha = transparency
    static Texture2D& getTexture2D(std::string name);

    // add text renderer
    static Text& getText(std::string name);
    static Text& loadText(GLuint width, GLuint height, std::string name);

    // memory free
    static void clear();
private:
    ResourceManager() { }
    static Shader loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile = nullptr);
    static Texture2D loadTexture2DFromFile(const char* file, bool alpha);
};

#endif