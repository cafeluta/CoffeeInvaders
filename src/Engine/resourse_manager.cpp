#include "../../include/Engine/resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../../lib/stb_image.h"

// initializing storage
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, Text> ResourceManager::Texts;  // fml * 2

Shader ResourceManager::loadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile, std::string name) {
    Shaders[name] = loadShaderFromFile(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
    return Shaders[name];
}

Shader& ResourceManager::getShader(std::string name) {
    return Shaders[name];
}

Texture2D ResourceManager::loadTexture2D(const char* file, bool alpha, std::string name) {
    Textures[name] = loadTexture2DFromFile(file, alpha);
    return Textures[name];
}

Texture2D& ResourceManager::getTexture2D(std::string name) {
    return Textures[name];
}

Text ResourceManager::loadText(GLuint width, GLuint height, std::string name) {
    Texts[name] = Text(width, height);
    return Texts[name];
}

Text& ResourceManager::getText(std::string name) {
    return Texts[name];
}

void ResourceManager::clear(){
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.id);
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.id);
}


// PRIVATE METHODS
Shader ResourceManager::loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try {
        // opening files
        std::ifstream vFile(vertexShaderFile);
        std::ifstream fFile(fragmentShaderFile);
        
        // string streams
        std::stringstream vStream, fStream;
        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();

        // closing files
        vFile.close();
        fFile.close();

        // extracting glsl code
        vertexCode = vStream.str();
        fragmentCode = fStream.str();

        if (geometryShaderFile != nullptr) {
            std::ifstream gFile(geometryShaderFile);
            std::stringstream gStream;
            gStream << gFile.rdbuf();
            gFile.close();
            geometryCode = gStream.str();
        }
    } catch (const std::exception& e) {
        std::cout << "ERROR::SHADER: Failed to read shader files: " << e.what() << std::endl;
    }
    
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();
    const char* geometryShaderCode = geometryCode.c_str();

    Shader shader;
    shader.compile(vertexShaderCode, fragmentShaderCode, geometryShaderFile != nullptr ? geometryShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTexture2DFromFile(const char* file, bool alpha) {
    Texture2D texture;

    if (alpha) {
        texture.InternalFormat = GL_RGBA;
        texture.ImageFormat = GL_RGBA;
    }
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << file << std::endl;
        return texture;
    }
    texture.generate(width, height, data);

    stbi_image_free(data);
    return texture;
}
