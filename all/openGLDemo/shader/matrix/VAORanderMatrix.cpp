//
//  VAORanderMatrix.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VAORanderMatrix.hpp"
#include "stb_image.h"

GLuint VAORanderMatrix:: createTexture(char const * path, GLuint pixelFormat, GLint param) {
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // 加载并生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}

void VAORanderMatrix::createVAO() {
    
    GLfloat vertices[] = {
        //  ---- 位置 ----      - 纹理坐标 -
        0.5f,  0.5f, 0.0f,     1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,     1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f    // 左上
    };

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    _VAO = VAO;
    
    _texture1 = createTexture("textures/container.jpg", GL_RGB, GL_REPEAT);
    _texture2 = createTexture("textures/awesomeface.jpg", GL_RGB, GL_REPEAT);
}

void VAORanderMatrix::beforeRander(GLuint program) {
    
    glUseProgram(program);

    /*
     记住，实际的变换顺序应该与阅读顺序相反：尽管在代码中我们旋转->缩小->位移，实际的变换却是位移->缩小->旋转。一定要注意变换顺序。
     这里的坐标变化，实际上都是以openGL坐标系为中心的，也就是说，旋转，放缩都是以坐标原点为中心进行的。
     这里的旋转需要注意，因为这里旋转的只是openGL的坐标系，也即 -1.0~1.0的坐标系，但是视口本身的大小没有修改，所以当旋转后，重新将openGL坐标映射到视口坐标上，会出现拉伸的现象。
     eg: 原来width:800,height:600. 即（-1，-1）映射到（0，0）、（1，-1）->（800，0）。
     旋转90度后，则原（-1，-1）变换到（1，-1），映射到窗口上则是（800，0）。同理（1，-1）->（800，600）。
     可以看到，原来的(-1,-1)到(1,-1)是一条底边，长度为800。旋转后则成了右边，长度为600。但实际上openGL坐标并没有变形，而是映射到视口产生的拉伸。
     可通过对视口大小也进行变换来保证纹理不拉伸形变
     */
    glm::mat4 trans(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0));
    /*
     glUniformMatrix4fv函数把矩阵数据发送给着色器。
     第一个参数是uniform的位置值。
     第二个参数告诉OpenGL我们将要发送多少个矩阵，这里是1。
     第三个参数询问我们我们是否希望对我们的矩阵进行置换(Transpose)，也就是说交换我们矩阵的行和列。OpenGL开发者通常使用一种内部矩阵布局，叫做列主序(Column-major Ordering)布局。GLM的默认布局就是列主序，所以并不需要置换矩阵，我们填GL_FALSE。
     最后一个参数是真正的矩阵数据，但是GLM并不是把它们的矩阵储存为OpenGL所希望接受的那种，因此我们要先用GLM的自带的函数value_ptr来变换这些数据。
     */
//    GLint transformLoc = glGetUniformLocation(program, "transform");
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    setMat4(program, "transform", trans);
    setInt(program, "texture1", 0);
    setInt(program, "texture2", 1);
}

void VAORanderMatrix::rander(GLuint program) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区, 之后颜色变为`glClearColor()`所设置的颜色

    glUseProgram(program);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texture2);
    
    glBindVertexArray(_VAO);
    {
        glm::mat4 trans(1.0f);
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0));
        setMat4(program, "transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    {
        glm::mat4 trans(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0));
        setMat4(program, "transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    {
        float scaleAmount = sin(glfwGetTime());
        glm::mat4 trans(1.0f);
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        trans = glm::translate(trans, glm::vec3(0.5, 0.5, 0));
        setMat4(program, "transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

