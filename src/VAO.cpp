//
// Created by shubh on 10/11/2021.
//

#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}


void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponentsn, GLenum type, GLsizeiptr stride, void *offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numComponentsn, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.UnBind();
}


void VAO::Bind() {
    glBindVertexArray(ID);
}

void VAO::UnBind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
}

