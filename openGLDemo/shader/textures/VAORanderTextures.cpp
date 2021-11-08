//
//  VAORanderTextures.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VAORanderTextures.hpp"
#include "stb_image.h"

/*
 第一个参数为图片路径，第二个参数为纹理环绕方式
 GL_REPEAT    对纹理的默认行为。重复纹理图像。
 GL_MIRRORED_REPEAT    和GL_REPEAT一样，但每次重复图片是镜像放置的。
 GL_CLAMP_TO_EDGE    纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
 GL_CLAMP_TO_BORDER    超出的坐标为用户指定的边缘颜色。
 */
GLuint VAORanderTextures:: createTexture(char const * path, GLint param = GL_REPEAT) {
    
    // 创建纹理的引用
    GLuint texture;
    glGenTextures(1, &texture);
    // 绑定2D纹理目标
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // 设置纹理对象环绕方式
    // glTexParameter*函数对单独的一个坐标轴设置, s轴、t轴、z轴 对应 x、y、z
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
    /*
     如果我们选择 GL_CLAMP_TO_BORDER 选项，我们还需要指定一个边缘的颜色。这需要使用 glTexParameter 函数的fv后缀形式。
     用GL_TEXTURE_BORDER_COLOR作为它的选项，并且传递一个float数组作为边缘的颜色值：
     */
    if (param == GL_CLAMP_TO_BORDER) {
        float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }

    /*
     设置纹理对象过滤方式
     纹理坐标不依赖于分辨率(Resolution)，它可以是任意浮点值，所以OpenGL需要知道怎样将纹理像素(Texture Pixel)映射到纹理坐标。
     当你有一个很大的物体但是纹理的分辨率很低的时候这就变得很重要了。纹理过滤有很多个选项，我们只讨论最重要的两种：
     GL_NEAREST（也叫邻近过滤，Nearest Neighbor Filtering）是OpenGL默认的纹理过滤方式。当设置为GL_NEAREST的时候，OpenGL会选择中心点最接近纹理坐标的那个像素。
     GL_LINEAR（也叫线性过滤，(Bi)linear Filtering）它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //当纹理被缩小(Minify)时，使用临近过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //当纹理被放大(Magnify)时，使用线性过滤
    
    // 加载并生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // 它需要三个int作为它的第二、第三和第四个参数，stb_image.h将会用图像的宽度、高度和颜色通道个数填充这三个变量。
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        //根据颜色通道处理纹理格式
        GLenum format = 0;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        
        /*
         载入图片数据，生成纹理。
         第一个参数指定了纹理目标(Target)。设置为 GL_TEXTURE_2D 意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到 GL_TEXTURE_1D 和 GL_TEXTURE_3D 的纹理不会受到影响）。
         第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
         第三个参数告诉OpenGL我们希望把纹理储存为何种格式。这里我们使用和原图同样的格式。
         第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
         第六个参数应该总是被设为0（历史遗留的问题）。
         第七个参数定义原图的颜色格式，这里使用颜色通道判断，
         第八个参数定义了源图的数据类型。这里是字节流，即char(byte)数组，我们传入对应值 GL_UNSIGNED_BYTE。
         最后一个参数是图像数据。
         */
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); //启用多级渐远纹理
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    // 生成纹理后，可以释放图片的内存
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void VAORanderTextures::createVAO() {
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    GLfloat vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
//    GLfloat vertices[] = {
//        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // 右assimp_lib上
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, -1.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   -1.0f, -1.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   -1.0f, 2.0f    // 左上
//    };

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    _VAO = VAO;
    
    _texture1 = createTexture("textures/container.jpg");
    _texture2 = createTexture("textures/awesomeface.png");
    
    _alpha = 0.2f;
}

void VAORanderTextures::beforeRander(GLuint program) {
    
    //注意，查询uniform地址不要求你之前使用过着色器程序，但是更新一个uniform之前你必须先使用程序（调用glUseProgram)，因为它是在当前激活的着色器程序中设置uniform的
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "texture1"), 0); // 手动设置
    glUniform1i(glGetUniformLocation(program, "texture2"), 1); // 手动设置
}

void VAORanderTextures::rander(GLuint program) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区, 之后颜色变为`glClearColor()`所设置的颜色

    glUseProgram(program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texture2);
    
    glUniform1f(glGetUniformLocation(program, "alpha"), _alpha); // 手动设置
    
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void VAORanderTextures::processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    //glfwGetKey 返回上一次特定窗口中某个按键的状态（按下GLFW_PRESS 或者 释放GLFW_RELEASE）
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        _alpha += 0.01f;
        if (_alpha >= 1.0f) {
            _alpha = 1.0f;
        }
    }else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        _alpha -= 0.01f;
        if (_alpha <= .0f) {
            _alpha = .0f;
        }
    }
}
