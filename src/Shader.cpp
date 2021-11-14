//
// Created by shubh on 10/11/2021.
//

#include "Shader.h"


std::string readFile(const char *filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return {contents};
    }
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {

    // Read and store Shader Files to List of characters
    std::string vertexCode = readFile(vertexFile);
    std::string fragmentCode = readFile(fragmentFile);
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Setup Vertex Shader and Compile it
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Setup Fragment Shader and Compile it
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Create Shader program and get store its reference in ID
    ID = glCreateProgram();

    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-Up | Link all shaders together into the shader program
    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

