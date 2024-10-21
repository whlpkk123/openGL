//
//  VAORanderTwoTriangleOther.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#include "VAORanderTwoTriangleOther.hpp"
#include <iostream>


void VAORanderTwoTriangleOther::createVAO() {
    
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);    // Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    
    _VAO = VAO;
}

void VAORanderTwoTriangleOther::rander(GLuint program) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区, 之后颜色变为`glClearColor()`所设置的颜色

    // 激活程序对象
    glUseProgram(program);

    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
