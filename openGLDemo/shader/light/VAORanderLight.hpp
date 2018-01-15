//
//  VAORanderLight.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef VAORanderLight_hpp
#define VAORanderLight_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "LightVAORander.hpp"

class VAORanderLight : public LightVAORander {
private:
    GLuint _VAO;
    GLuint _lightVAO;
    glm::vec3 _lightPos;
public:
    void createVAO();
    void rander(GLuint program, GLuint lightProgram);
    void beforeRander(GLuint program, GLuint lightProgram);
};

#endif /* VAORanderLight_hpp */
