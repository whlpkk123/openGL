//
//  VAORanderUniformOffset.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VAORanderUniformOffset.hpp"
#include <iostream>


#include <math.h>

void VAORanderUniformOffset::createVAO() {
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // position左下
        0.5f, -0.5f, 0.0f,  // position右下
        0.0f,  0.5f, 0.0f   // position顶部
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); //
    
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    _VAO = VAO;
}

void VAORanderUniformOffset::rander(GLuint program) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区, 之后颜色变为`glClearColor()`所设置的颜色
    
    // 激活程序对象
    glUseProgram(program);
    
    //注意，查询uniform地址不要求你之前使用过着色器程序，但是更新一个uniform之前你必须先使用程序（调用glUseProgram)，因为它是在当前激活的着色器程序中设置uniform的
    GLint vertexOffset = glGetUniformLocation(program, "xOffset");
    glUniform1f(vertexOffset, 0.5f);

    // 绘制
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
