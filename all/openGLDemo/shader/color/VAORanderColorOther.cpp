//
//  VAORanderColorOther.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#include "VAORanderColorOther.hpp"
#include <iostream>

void VAORanderColorOther::createVAO() {
    
    GLfloat vertices[] = {
        // 位置              // 颜色
        0.9f, -0.9f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.9f, -0.9f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.9f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
    
    GLuint VAO,VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    /*
     glVertexAttribPointer 函数告诉OpenGL该如何解析顶点数据
     第一个参数指定我们要配置的顶点属性的位置。 我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)。
     第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
     第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中向量vec*都是由浮点数值组成的)。
     第四个参数参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
     第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在6个float之后，我们把步长设置为6 * sizeof(GLfloat)。 要注意的是由于我们知道这个数组不是紧密排列的（在两个顶点属性之间有空隙），所以这里不能设置为0。
     最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，是0，颜色数组是3*sizeof(GLfloat)。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    _VAO = VAO;
}

void VAORanderColorOther::rander(GLuint program) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区, 之后颜色变为`glClearColor()`所设置的颜色
    
    // 激活程序对象
    glUseProgram(program);
    
    // 绘制
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
