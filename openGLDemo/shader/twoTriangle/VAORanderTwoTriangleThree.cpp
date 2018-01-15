//
//  VAORanderTwoTriangleThree.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VAORanderTwoTriangleThree.hpp"
#include <iostream>



void VAORanderTwoTriangleThree::createVAO() {
    
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top

        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };
    
    GLuint indices[] = {
        0, 1, 2,
        1, 3, 4
    };
    
    /*
     索引缓冲对象(Element Buffer Object，EBO，也叫Index Buffer Object，IBO)。
     只储存不同的顶点，并设定绘制这些顶点的顺序。这样子我们只要储存4个顶点就能绘制矩形了，之后只要指定绘制的顺序就行了。
     索引缓冲对象的工作方式正是这样的。和顶点缓冲对象一样，EBO也是一个缓冲，它专门储存索引，OpenGL调用这些顶点的索引来决定该绘制哪个顶点。所谓的索引绘制(Indexed Drawing)正是我们问题的解决方案。
     */
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    
    // 同VBO一样，将新创建的缓冲对象绑定到 GL_ELEMENT_ARRAY_BUFFER 目标上
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 将索引数据写入buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);    // Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    _VAO = VAO;
}

void VAORanderTwoTriangleThree::rander(GLuint program) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区, 之后颜色变为`glClearColor()`所设置的颜色

    // 激活程序对象
    glUseProgram(program);
    
    // VAO同样可以保存EBO的绑定状态。VAO绑定时正在绑定的EBO会被保存为VAO的元素缓冲对象。绑定VAO的同时也会自动绑定EBO。
    glBindVertexArray(_VAO);
    // 通过 glPolygonMode 函数配置OpenGL如何绘制图元。第一个参数表示我们打算将其应用到正面和背面，第二个参数告诉我们用线来绘制(不填充，默认为GL_FILL)。
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDrawElements 替换 glDrawArrays，来指明我们从索引缓冲渲染。使用glDrawElements时，我们会使用当前绑定的索引缓冲对象中的索引进行绘制：
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
