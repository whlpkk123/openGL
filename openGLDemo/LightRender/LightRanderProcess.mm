//
//  Rander.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "LightRanderProcess.hpp"
#include <iostream>


#include "VertexShader.hpp"
#include "FragmentShader.hpp"
#include "ShaderProgram.hpp"


using namespace std;

#pragma mark - Declaration

void l_processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods);
void l_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void l_mouse_callback(GLFWwindow* window, double xpos, double ypos);
void l_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

LightVAORander *_lightRander;

float lastX = 0;
float lastY = 0;
bool firstMouse = true;

// timing
float _deltaTime = 0.0f;
float _lastFrame = 0.0f;

Camera _l_camera(glm::vec3(0.0f, 0.0f, 3.0f));

void LightRanderProcess::createLightRanderProcess(NSString *vertexShaderPath, NSString *fragmentShaderPath, NSString *lightVertexShaderPath, NSString *lightFragmentShaderPath,LightVAORander *rander) {

    _lightRander = rander;
    _lightRander->_camera = &_l_camera;
    
    GLFWwindow *window;
    if (!glfwInit()) {
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主版本3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次版本3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 在mac上需要设置, 向前兼容
    
    window = glfwCreateWindow(800, 600, "Hi, OpenGL!", NULL, NULL);
    if (!window) {
        cout << "GLFW create window error" << window << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    _lightRander->_screenWidth = 800;
    _lightRander->_screenHeight = 600;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, l_framebuffer_size_callback);
    glfwSetKeyCallback(window, l_processInputEvent);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, l_mouse_callback);
    glfwSetScrollCallback(window, l_scroll_callback);

    glEnable(GL_DEPTH_TEST);//启用深度测试
    _lightRander->handleWindow(window);
    
    
    VertexShader vShader;
    GLuint vertexShader = vShader.createShader(vertexShaderPath);
    
    FragmentShader fShader;
    GLuint fragmentShader = fShader.createShader(fragmentShaderPath);
    
    ShaderProgram program;
    GLuint shaderProgram = program.linkVertexShader(vertexShader, fragmentShader);
    
    
    VertexShader lightvShader;
    GLuint lightVertexShader = lightvShader.createShader(lightVertexShaderPath);
    
    FragmentShader lightfShader;
    GLuint lightFragmentShader = lightfShader.createShader(lightFragmentShaderPath);
    
    ShaderProgram lightProgram;
    GLuint lightShaderProgram = lightProgram.linkVertexShader(lightVertexShader, lightFragmentShader);
    
    _lightRander->createVAO();
    _lightRander->beforeRander(shaderProgram, lightShaderProgram);
    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;
        
        _lightRander->rander(shaderProgram, lightShaderProgram);
        
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
void l_processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods) {
//    cout<< "key is:" << key <<endl;
//    cout<< "scanCode is:" << scanCode <<endl;
//    cout<< "action is:" << action <<endl;
//    cout<< "mods is:" << mods <<endl;
    
    //glfwGetKey 返回上一次特定窗口中某个按键的状态（按下GLFW_PRESS 或者 释放GLFW_RELEASE）
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true); // 设置window关闭flag，注意线程安全
    }else {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            _l_camera.ProcessKeyboard(FORWARD, _deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            _l_camera.ProcessKeyboard(BACKWARD, _deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            _l_camera.ProcessKeyboard(LEFT, _deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            _l_camera.ProcessKeyboard(RIGHT, _deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            _l_camera.ProcessKeyboard(UP, _deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            _l_camera.ProcessKeyboard(DOWN, _deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            _l_camera.getCameraInfo();
        }

        
        _lightRander->processInputEvent(window, key, scanCode, action, mods);
    }
}

void l_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    
    _lightRander->_screenWidth = width;
    _lightRander->_screenHeight = height;
}

void l_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    
    _l_camera.ProcessMouseMovement(xoffset, yoffset);
}

void l_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    _l_camera.ProcessMouseScroll(yoffset);
}
