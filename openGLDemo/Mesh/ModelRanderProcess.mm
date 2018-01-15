//
//  ModelRanderProcess.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/24.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "ModelRanderProcess.hpp"
#include "Camera.hpp"
//#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>

void m_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void m_processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods);
void m_mouse_callback(GLFWwindow* window, double xpos, double ypos);
void m_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float _m_lastX = 0;
float _m_lastY = 0;
bool _m_firstMouse = true;

// timing
float _m_deltaTime = 0.0f;
float _m_lastFrame = 0.0f;

Camera _m_camera(glm::vec3(0.0f, 0.0f, 3.0f));

int _m_screenWidth = 0;
int _m_screenHeight = 0;

void ModelRanderProcess::createModelRanderProcess(NSString *vertexShaderPath, NSString *fragmentShaderPath, NSString *modelPath) {
    
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
    _m_screenWidth = 800;
    _m_screenHeight = 600;
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, m_framebuffer_size_callback);
    glfwSetKeyCallback(window, m_processInputEvent);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, m_mouse_callback);
    glfwSetScrollCallback(window, m_scroll_callback);
    
    glEnable(GL_DEPTH_TEST);//启用深度测试

    Shader shader(vertexShaderPath, fragmentShaderPath);
    Model ourModel(modelPath.UTF8String);
    
    shader.use();
    //设置定向光参数
    shader.setVec3("dirLight.direction",  -2.2f, -0.5f, -3.3f);
    shader.setVec3("dirLight.ambient",  0.8f, 0.8f, 0.8f);
    shader.setVec3("dirLight.diffuse",  1.0f, 1.0f, 1.0f);
    shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    
    //设置聚光源参数
    shader.setVec3("spotlight.ambient",  0.0f, 0.0f, 0.0f);
    shader.setVec3("spotlight.diffuse",  1.0f, 1.0f, 1.0f);
    shader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("spotlight.constant",  1.0f);
    shader.setFloat("spotlight.linear",    0.09f);
    shader.setFloat("spotlight.quadratic", 0.032f);
    shader.setFloat("spotlight.cutOff",  glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotlight.outerCutOff",  glm::cos(glm::radians(17.5f)));
    
    
    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        _m_deltaTime = currentFrame - _m_lastFrame;
        _m_lastFrame = currentFrame;
        
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        
        glm::mat4 projection = glm::perspective(glm::radians(_m_camera.Zoom), (float)_m_screenWidth / (float)_m_screenHeight, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        glm::mat4 view = _m_camera.GetViewMatrix();
        shader.setMat4("view", view);
        
        // render the loaded model
        glm::mat4 modelMat;
        modelMat = glm::translate(modelMat, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        modelMat = glm::scale(modelMat, glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
        shader.setMat4("model", modelMat);
        
        shader.setVec3("spotlight.position",  _m_camera.Position);
        shader.setVec3("spotlight.direction",  _m_camera.Front);
        shader.setVec3("viewPos", _m_camera.Position);

        ourModel.Draw(shader);
        
        glfwPollEvents(); // 监听事件
        glfwSwapBuffers(window); // 颜色缓冲区存储着GLFW窗口每一个像素颜色
    }
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


void m_processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    //glfwGetKey 返回上一次特定窗口中某个按键的状态（按下GLFW_PRESS 或者 释放GLFW_RELEASE）
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true); // 设置window关闭flag，注意线程安全
    }else {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            _m_camera.ProcessKeyboard(FORWARD, _m_deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            _m_camera.ProcessKeyboard(BACKWARD, _m_deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            _m_camera.ProcessKeyboard(LEFT, _m_deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            _m_camera.ProcessKeyboard(RIGHT, _m_deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            _m_camera.ProcessKeyboard(UP, _m_deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            _m_camera.ProcessKeyboard(DOWN, _m_deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            _m_camera.getCameraInfo();
        }
    }
}

void m_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    
    _m_screenWidth = width;
    _m_screenHeight = height;
}

void m_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (_m_firstMouse)
    {
        _m_lastX = xpos;
        _m_lastY = ypos;
        _m_firstMouse = false;
    }
    
    float xoffset = xpos - _m_lastX;
    float yoffset = _m_lastY - ypos; // reversed since y-coordinates go from bottom to top
    _m_lastX = xpos;
    _m_lastY = ypos;
    
    _m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void m_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    _m_camera.ProcessMouseScroll(yoffset);
}
