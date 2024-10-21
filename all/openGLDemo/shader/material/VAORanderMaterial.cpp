//
//  VAORanderMaterial.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VAORanderMaterial.hpp"
#include <iostream>

void VAORanderMaterial::createVAO() {
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    
    
    GLuint VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1); //
    
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);
    
    GLuint normals_vbo = 0;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    _VAO = VAO1;
    
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);
    _lightVAO = lightVAO;
}

void VAORanderMaterial::beforeRander(GLuint program, GLuint lightProgram) {
    _camera->setCameraInfo(glm::vec3(1.20981f, 1.32813f, 3.87309f), -108.397f, -14.3445f);
    
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    _lightPos = lightPos;
    
    glUseProgram(program);
    
    setVec3(program, "material.ambient",  1.0f, 0.5f, 0.31f);
    setVec3(program, "material.diffuse",  1.0f, 0.5f, 0.31f);
    setVec3(program, "material.specular", 0.5f, 0.5f, 0.5f);
    setFloat(program, "material.shininess", 32.0f);
    
    
    setVec3(program, "light.ambient",  0.2f, 0.2f, 0.2f);
    setVec3(program, "light.diffuse",  0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
    setVec3(program, "light.specular", 1.0f, 1.0f, 1.0f);
}


void VAORanderMaterial::rander(GLuint program, GLuint lightProgram) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glUseProgram(program);
    setVec3(program, "objectColor", 1.0f, 0.5f, 0.31f);
    setVec3(program, "lightColor", 1.0f, 1.0f, 1.0f);

    glm::mat4 model;
    setMat4(program, "model", model);

    glm::mat4 view = _camera->GetViewMatrix();
    setMat4(program, "view", view);

    //投影矩阵,我们希望在场景中使用透视投影
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(_camera->Zoom), _screenWidth / (float)(_screenHeight), 0.1f, 100.0f);
    setMat4(program, "projection", projection);
    
    
    
    setVec3(program, "viewPos", _camera->Position);
    glm::mat4 rotate;
//    rotate = glm::rotate(rotate, (float)glfwGetTime()/5.0f, glm::vec3(-1.0f, 0.0f, 1.0f));
    glm::vec4 lightPos = rotate * glm::vec4(_lightPos,1.0);
    setVec3(program, "lightPos", glm::vec3(lightPos));
    
    
    glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);
    
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响
    
    setVec3(program, "light.ambient", ambientColor);
    setVec3(program, "light.diffuse", diffuseColor);

    // 绘制
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glUseProgram(lightProgram);
    setMat4(lightProgram, "view", view);
    setMat4(lightProgram, "projection", projection);

    model = glm::mat4();
//    model = glm::rotate(model, (float)glfwGetTime()/5.0f, glm::vec3(-1.0f, 0.0f, 1.0f));
    model = glm::translate(model, _lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    setMat4(lightProgram, "model", model);
    
    glBindVertexArray(_lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
