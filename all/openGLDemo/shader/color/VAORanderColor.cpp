//
//  VAORanderColor.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VAORanderColor.hpp"
#include <iostream>

/*
 我们通过顶点缓冲对象(Vertex Buffer Objects, VBO)管理这个内存，它会在GPU内存（通常被称为显存）中储存大量顶点属性。
 使用这些缓冲对象的好处是我们可以一次性的发送一大批数据到显卡上，而不是每个顶点发送一次。从CPU把数据发送到显卡相对较慢，所以只要可能我们都要尝试尽量一次性发送尽可能多的数据。当数据发送至显卡的内存中后，顶点着色器几乎能立即访问顶点，这是个非常快的过程。

 顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象(VBO)那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。
 这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的VAO就行了。
 
 一个 VBO 就是一片缓冲区，即显存，可以存放大量数据。glBindBuffer GL_ARRAY_BUFFER 向显存内部写入数组，在根据 glVertexAttribPointer 解析数组即可，也就是一片缓存区可以存放多个顶点属性，只需要根据对应的规则解析即可。
 VAO不是Buffer-Object，所以不用作存储数据；VAO保存的是VBO的绘制状态。VAO将其对应的VBO的状态及信息直接存储在GPU的内存中。VAO中并没有VBO的相关属性数据，只是存储了VBO的当前状态及索引信息，通过VAO就能快速访问到VBO的状态及VBO的数据。
 VAO 还包含 索引缓冲对象（Element Buffer Object，EBO）的状态及索引
 */

void VAORanderColor::createVAO() {
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // position左下
        0.5f, -0.5f, 0.0f,  // position右下
        0.0f,  0.5f, 0.0f   // position顶部
    };
    
    GLfloat colours[] = {
        1.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, 0.0f,  1.0f
    };
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); //
    
    // 顶点缓冲对象(Vertex Buffer Objects, VBO)，创建VBO对象的ID引用
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    // 使用 glBindBuffer 函数把新创建的缓冲对象绑定到GL_ARRAY_BUFFER目标上
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    // 从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。然后我们可以调用 glBufferData 函数，它会把之前定义的顶点数据写入到buffer中：
    /*
     glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。第三个参数是我们希望发送的实际数据。
     第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
     GL_STATIC_DRAW ：数据不会或几乎不会改变。
     GL_DYNAMIC_DRAW：数据会被改变很多。
     GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
     glVertexAttribPointer 函数告诉OpenGL该如何解析顶点数据
     第一个参数指定我们要配置的 属性位置值。 我们在顶点着色器中使用layout(location = 0)定义了position 顶点属性的位置值(Location)。这里我们传入0。
     第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
     第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中向量vec*都是由浮点数值组成的)。
     第四个参数参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
     第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(GLfloat)。 要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
     最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    
    GLuint colours_vbo = 0;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    
    // 使用glEnableVertexAttribArray,以 属性位置值 作为参数，启用顶点属性；顶点属性默认是禁用的。
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    // 清楚 VAO 和 VBO 目标的绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    _VAO = VAO;
}

void VAORanderColor::rander(GLuint program) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区, 之后颜色变为`glClearColor()`所设置的颜色
    
    // 激活程序对象
    glUseProgram(program);
    
    // 通过绑定VAO，间接绑定VBO
    glBindVertexArray(_VAO);
    // 使用VBO定义的顶点属性绘制图元
    /*
     glDrawArrays函数第一个参数是我们打算绘制的OpenGL图元的类型。绘制一个三角形，这里传递GL_TRIANGLES给它。
     第二个参数指定了顶点数组的起始索引，我们这里填0。
     最后一个参数指定我们打算绘制多少个顶点，这里是3（我们只从我们的数据中渲染一个三角形，它只有3个顶点长）。
     */
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
