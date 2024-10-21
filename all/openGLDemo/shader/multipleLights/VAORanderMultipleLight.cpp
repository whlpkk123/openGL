//
//  VAORanderMultipleLight.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#include "VAORanderMultipleLight.hpp"
#include <iostream>

#include "stb_image.h"
#include <cstdlib>


GLuint VAORanderMultipleLight:: createTexture(char const * path, GLint param) {
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
        GLenum format = 0;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return texture;
}


void VAORanderMultipleLight::createVAO() {
    
    GLfloat vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    
    
    GLuint VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1); //
    
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);
    
    GLuint normals_vbo = 0;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    GLuint textures_vbo = 0;
    glGenBuffers(1, &textures_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, textures_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    _VAO = VAO1;
    
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);
    _lightVAO = lightVAO;
    
    
    _texture = createTexture("lightingMaps/container2.png", GL_REPEAT);
    _texture2 = createTexture("lightingMaps/container2_specular.png", GL_REPEAT);
}

void VAORanderMultipleLight::beforeRander(GLuint program, GLuint lightProgram) {
    
    _camera->setCameraInfo(glm::vec3(1.37506f, 0.776235f, 3.20087f), -101.001f, -15.3027f);
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    memcpy(_cubePositions, cubePositions, sizeof(cubePositions));
    
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    memcpy(_pointLightPositions, pointLightPositions, sizeof(pointLightPositions));

    
    glUseProgram(program);
    
    //设置材质
    setInt(program, "material.diffuse", 0);
    setInt(program, "material.specular", 1);
    setInt(program, "material.emission", 2);
    setFloat(program, "material.shininess", 64.0f);
    
    //设置定向光参数
    setVec3(program, "dirLight.direction",  -0.2f, -1.0f, -0.3f);
    setVec3(program, "dirLight.ambient",  0.05f, 0.05f, 0.05f);
    setVec3(program, "dirLight.diffuse",  0.4f, 0.4f, 0.4f); // 将光照调暗了一些以搭配场景
    setVec3(program, "dirLight.specular", 0.5f, 0.5f, 0.5f);
    
    //设置点光源参数
    for (int i=0; i<4; i++) {
        setVec3(program, "pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
        setVec3(program, "pointLights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
        setVec3(program, "pointLights[" + std::to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
        setVec3(program, "pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
        setFloat(program, "pointLights[" + std::to_string(i) + "].constant", 1.0f);
        setFloat(program, "pointLights[" + std::to_string(i) + "].linear", 0.09);
        setFloat(program, "pointLights[" + std::to_string(i) + "].quadratic", 0.032);
    }
    
    //设置聚光源参数
    setVec3(program, "spotlight.ambient",  0.0f, 0.0f, 0.0f);
    setVec3(program, "spotlight.diffuse",  1.0f, 1.0f, 1.0f);
    setVec3(program, "spotlight.specular", 1.0f, 1.0f, 1.0f);
    setFloat(program, "spotlight.constant",  1.0f);
    setFloat(program, "spotlight.linear",    0.09f);
    setFloat(program, "spotlight.quadratic", 0.032f);
    setFloat(program, "spotlight.cutOff",  glm::cos(glm::radians(12.5f)));
    setFloat(program, "spotlight.outerCutOff",  glm::cos(glm::radians(17.5f)));
}


void VAORanderMultipleLight::rander(GLuint program, GLuint lightProgram) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    
    glm::mat4 view = _camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(_camera->Zoom), _screenWidth / (float)(_screenHeight), 0.1f, 100.0f);
    
    
    glUseProgram(lightProgram);
    glBindVertexArray(_lightVAO);
    setMat4(lightProgram, "view", view);
    setMat4(lightProgram, "projection", projection);
    for(unsigned int i = 0; i < 4; i++) {
        glm::mat4 model;
        model = glm::translate(model, _pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.2f));
        setMat4(lightProgram, "model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    
    glUseProgram(program);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texture2);
    
    setMat4(program, "view", view);
    setMat4(program, "projection", projection);

    setVec3(program, "viewPos", _camera->Position);
    setVec3(program, "spotlight.position",  _camera->Position);
    setVec3(program, "spotlight.direction",  _camera->Front);

    glBindVertexArray(_VAO);
    for(unsigned int i = 0; i < 10; i++) {
        glm::mat4 model;
        model = glm::translate(model, _cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        setMat4(program, "model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
