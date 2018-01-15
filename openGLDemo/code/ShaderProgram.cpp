//
//  ShaderProgram.cpp
//  openGLDemo
//
//  Created by xindong on 2018/3/6.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "ShaderProgram.hpp"
#include "glad.h"

#include <iostream>

using namespace std;

GLuint ShaderProgram:: linkVertexShader(GLuint vertexShader, GLuint fragmentShader) {
    if (!vertexShader || !fragmentShader) {
        cout << "shader cann't be nil" << vertexShader << fragmentShader << endl;
        return -1;
    }
    
    // glCreateProgram函数创建一个程序，并返回新创建程序对象的ID引用。
    GLuint program = glCreateProgram();
    // 附加编译的着色器到程序对象上
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    // 用 glLinkProgram 链接它们
    glLinkProgram(program);
    
    // 链接错误检测，类似 VertexShader 顶点着色器的检测
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "The shader link error😡: " << infoLog << endl;
        return -1;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}
