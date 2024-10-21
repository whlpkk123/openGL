//
//  LightVAORander.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef LightVAORander_hpp
#define LightVAORander_hpp

#include <stdio.h>
#include <iostream>
#include <OpenGL/gltypes.h>
#include "glad.h"
#include "glfw3.h"

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "Camera.hpp"

class LightVAORander {
public:
    int _screenWidth;
    int _screenHeight;
    Camera *_camera;

    virtual void createVAO() = 0;
    virtual void rander(GLuint program, GLuint lightProgram) = 0;
    virtual void beforeRander(GLuint program, GLuint lightProgram);
    virtual void processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods);
    virtual void handleWindow(GLFWwindow *window);
    
    void setBool(GLuint program, const std::string &name, bool value) const;
    void setInt(GLuint program, const std::string &name, int value) const;
    void setFloat(GLuint program, const std::string &name, float value) const;
    void setVec2(GLuint program, const std::string &name, const glm::vec2 &value) const;
    void setVec2(GLuint program, const std::string &name, float x, float y) const;
    void setVec3(GLuint program, const std::string &name, const glm::vec3 &value) const;
    void setVec3(GLuint program, const std::string &name, float x, float y, float z) const;
    void setVec4(GLuint program, const std::string &name, const glm::vec4 &value) const;
    void setVec4(GLuint program, const std::string &name, float x, float y, float z, float w) const;
    void setMat2(GLuint program, const std::string &name, const glm::mat2 &mat) const;
    void setMat3(GLuint program, const std::string &name, const glm::mat3 &mat) const;
    void setMat4(GLuint program, const std::string &name, const glm::mat4 &mat) const;
};

#endif /* LightVAORander_hpp */
