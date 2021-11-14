//
// Created by shubh on 10/11/2021.
//

#pragma once
#include <GL/glew.h>

class EBO {
public:
    GLuint ID;

    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void UnBind();
    void Delete();

};