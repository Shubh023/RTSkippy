//
// Created by shubh on 10/11/2021.
//

#pragma once
#include <GL/glew.h>
#include <VBO.h>

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void UnBind();
    void Delete();

};