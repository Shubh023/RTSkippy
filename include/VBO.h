//
// Created by shubh on 10/11/2021.
//

#pragma once
#include <GL/glew.h>

class VBO {
public:
    GLuint ID;

    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void UnBind();
    void Delete();

};