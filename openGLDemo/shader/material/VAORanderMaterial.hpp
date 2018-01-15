//
//  VAORanderMaterial.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef VAORanderMaterial_hpp
#define VAORanderMaterial_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "LightVAORander.hpp"

class VAORanderMaterial : public LightVAORander {
private:
    GLuint _VAO;
    GLuint _lightVAO;
    glm::vec3 _lightPos;
public:
    void createVAO();
    void rander(GLuint program, GLuint lightProgram);
    void beforeRander(GLuint program, GLuint lightProgram);
};

#endif /* VAORanderMaterial_hpp */
