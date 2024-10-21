//
//  VAORanderMatrixOther.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef VAORanderMatrixOther_hpp
#define VAORanderMatrixOther_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"
#include <iostream>

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

class VAORanderMatrixOther : public VAORander {
private:
    GLuint _VAO;
    GLuint _texture1;
    GLuint _texture2;
public:
    void createVAO();
    void beforeRander(GLuint program);
    void rander(GLuint program);
    
    GLuint createTexture(char const * path, GLuint pixelFormat, GLint param);
};

#endif /* VAORanderMatrixOther_hpp */
