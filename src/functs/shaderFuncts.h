#ifndef SHADEFUNCT
#define SHADEFUNCT

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../shader.h"

// constructor generates the shader on the fly
// ------------------------------------------------------------------------
Shader compileShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) {

    Shader shader;

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();			
        // if geometry shader path is present, also load a geometry shader
        if(geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // checkCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if(geometryPath != nullptr)
    {
        const char * gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        // checkCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    shader.ID = glCreateProgram();
    glAttachShader(shader.ID, vertex);
    glAttachShader(shader.ID, fragment);
    if(geometryPath != nullptr)
        glAttachShader(shader.ID, geometry);
    glLinkProgram(shader.ID);
    // checkCompileErrors(shader.ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath != nullptr)
        glDeleteShader(geometry);

    return shader;
}

// activate the shader
// ------------------------------------------------------------------------
inline void use(Shader shader) { 
    glUseProgram(shader.ID); 
}

// utility uniform functions
// ------------------------------------------------------------------------
inline void setBool(Shader shader, const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(shader.ID, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
inline void setInt(Shader shader, const std::string &name, int value) { 
    glUniform1i(glGetUniformLocation(shader.ID, name.c_str()), value); 
}
// ------------------------------------------------------------------------
inline void setFloat(Shader shader, const std::string &name, float value) { 
    glUniform1f(glGetUniformLocation(shader.ID, name.c_str()), value); 
}
// ------------------------------------------------------------------------
inline void setVec2(Shader shader, const std::string &name, const glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(shader.ID, name.c_str()), 1, &value[0]); 
}
inline void setVec2(Shader shader, const std::string &name, float x, float y) {
    glUniform2f(glGetUniformLocation(shader.ID, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
inline void setVec3(Shader shader, const std::string &name, const glm::vec3 &value) { 
    glUniform3fv(glGetUniformLocation(shader.ID, name.c_str()), 1, &value[0]); 
}
inline void setVec3(Shader shader, const std::string &name, float x, float y, float z) { 
    glUniform3f(glGetUniformLocation(shader.ID, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
inline void setVec4(Shader shader, const std::string &name, const glm::vec4 &value) { 
    glUniform4fv(glGetUniformLocation(shader.ID, name.c_str()), 1, &value[0]); 
}
inline void setVec4(Shader shader, const std::string &name, float x, float y, float z, float w) { 
    glUniform4f(glGetUniformLocation(shader.ID, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
inline void setMat2(Shader shader, const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(shader.ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
inline void setMat3(Shader shader, const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(shader.ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
inline void setMat4(Shader shader, const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// // utility function for checking shader compilation/linking errors.
// // ------------------------------------------------------------------------
// void checkCompileErrors(GLuint shader, std::string type)
// {
//     GLint success;
//     GLchar infoLog[1024];
//     if(type != "PROGRAM")
//     {
//         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//         if(!success)
//         {
//             glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//             std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//         }
//     }
//     else
//     {
//         glGetProgramiv(shader, GL_LINK_STATUS, &success);
//         if(!success)
//         {
//             glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//             std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//         }
//     }
// }

#endif