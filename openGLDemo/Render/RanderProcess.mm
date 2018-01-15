//
//  Rander.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "RanderProcess.hpp"
#include <iostream>

#include "VertexShader.hpp"
#include "FragmentShader.hpp"
#include "ShaderProgram.hpp"

using namespace std;

#pragma mark - Declaration

void processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

VAORander *_rander;

void RanderProcess:: createRanderProcess(NSString *vertexShaderPath, NSString *fragmentShaderPath, VAORander *rander) {
    
    _rander = rander;
    
    // 初始化 GLFW
    if (!glfwInit()) {
        return;
    }
    
    // 使用 glfwWindowHint 函数配置 GLFW, 如下配置版本3.3、核心模式
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主版本3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次版本3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 在mac上需要设置, 向前兼容
    
    // 创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被 GLFW 的其他函数频繁地用到
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hi, OpenGL!", NULL, NULL);
    if (!window) {
        cout << "GLFW create window error" << window << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    _rander->_screenWidth = 800;
    _rander->_screenHeight = 600;
    
    // 显示当前窗口
    glfwMakeContextCurrent(window);
    
    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // 注册窗口大小变化回调事件，这里我们命名为 framebuffer_size_callback（见下面），当窗口调整大小的时候会回调到这个函数。 当窗口被第一次显示的时候也会回调。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 注册键盘回调事件
    glfwSetKeyCallback(window, processInputEvent);
    
    _rander->handleWindow(window);
    
    
    VertexShader vShader;
    GLuint vertexShader = vShader.createShader(vertexShaderPath);

    FragmentShader fShader;
    GLuint fragmentShader = fShader.createShader(fragmentShaderPath);

    ShaderProgram program;
    GLuint shaderProgram = program.linkVertexShader(vertexShader, fragmentShader);

    rander->createVAO();
    rander->beforeRander(shaderProgram);
    
    /*
     glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
     glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
     glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
     */
    while (!glfwWindowShouldClose(window)) {

        rander->rander(shaderProgram);
        
        glfwPollEvents(); // 监听事件
        /**
         应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。 这是因为生成的图像不是一下子被绘制出来
         的，而是按照从左到右，由上而下逐像素地绘制而成的。最终图像不是在瞬间显示给用户，而是通过一步一步生成的，这会
         导致渲染的结果很不真实。为了规避这些问题，我们应用双缓冲渲染窗口应用程序。前缓冲保存着最终输出的图像，它会在
         屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓
         冲，这样图像就立即呈显出来，之前提到的不真实感就消除了。
         */
        glfwSwapBuffers(window); // 颜色缓冲区存储着GLFW窗口每一个像素颜色
    }
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/**
 按键回调
 
 @param window 窗口
 @param key 被按下的键
 @param scanCode 按键的系统扫描代码
 @param action 被按下还是被释放
 @param mods 表示是否有Ctrl、Shift、Alt等按钮操作
 */
void processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods) {
//    cout<< "key is:" << key <<endl;
//    cout<< "scanCode is:" << scanCode <<endl;
//    cout<< "action is:" << action <<endl;
//    cout<< "mods is:" << mods <<endl;
    
    //glfwGetKey 返回上一次特定窗口中某个按键的状态（按下:GLFW_PRESS , 释放:GLFW_RELEASE）
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        //判断如果用户按下了返回键(Esc)（如果没有按下，glfwGetKey将会返回GLFW_RELEASE）。关闭 window
        glfwSetWindowShouldClose(window, true); // 设置window关闭flag，注意线程安全
    }else {
        _rander->processInputEvent(window, key, scanCode, action, mods);
    }
}


/// 窗口大小修改回调
/// @param window 窗口
/// @param width 新的宽度
/// @param height 新的高度
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    
    _rander->_screenWidth = width;
    _rander->_screenHeight = height;
}
