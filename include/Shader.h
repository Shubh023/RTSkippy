//
// Created by shubh on 10/11/2021.
//

#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string readFile(const char* filename);

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
};
