#include "../../include/Engine/shader.h"

#include <iostream>

Shader &Shader::use() {
    glUseProgram(this->id);
    return *this;
}

void Shader::compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
    GLuint vertex, fragment, geometry;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // geometry shader if we have one
    // this is for animations and custom geometry
    if (geometrySource != nullptr) {
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometrySource, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }

    // shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    if (geometrySource != nullptr)
        glAttachShader(this->id, geometry);
    glLinkProgram(this->id);
    checkCompileErrors(this->id, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometrySource != nullptr)
        glDeleteShader(vertex);
}

void Shader::setFloat(const char *name, float value, bool useShader) {
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setInteger(const char *name, int value, bool useShader) {
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setVector2f(const char *name, float x, float y, bool useShader) {
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), x, y);
}

void Shader::setVector2f(const char *name, const glm::vec2 &value, bool useShader) {
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}

void Shader::setVector3f(const char *name, float x, float y, float z, bool useShader) {
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}

void Shader::setVector3f(const char *name, const glm::vec3 &value, bool useShader) {
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char *name, float x, float y, float z, float w, bool useShader) {
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::setVector4f(const char *name, const glm::vec4 &value, bool useShader) {
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char *name, const glm::mat4 &matrix, bool useShader) {
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
