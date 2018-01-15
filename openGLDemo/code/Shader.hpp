//
//  Shader.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/24.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <iostream>
#include "glm.hpp"

#import <Foundation/Foundation.h>

class Shader
{
public:
    unsigned int _programID;
    
//    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(NSString* vertexPath, NSString* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};

#endif /* Shader_hpp */
