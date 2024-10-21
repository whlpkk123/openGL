//
//  VAORanderLightingCastersDirectionalLight.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef VAORanderLightingCastersDirectionalLight_hpp
#define VAORanderLightingCastersDirectionalLight_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "LightVAORander.hpp"

class VAORanderLightingCastersDirectionalLight : public LightVAORander {
private:
    GLuint _VAO;
    glm::vec3 _cubePositions[10];

    GLuint _texture; //漫反射纹理
    GLuint _texture2; //镜面反射纹理
    GLuint _texture3; //放射光纹理
public:
    void createVAO();
    void rander(GLuint program, GLuint lightProgram);
    void beforeRander(GLuint program, GLuint lightProgram);
    
    GLuint createTexture(char const * path, GLint param);
};

#endif /* VAORanderLightingCastersDirectionalLight_hpp */
