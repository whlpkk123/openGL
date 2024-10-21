//
//  VAORanderMatrixCoordinate.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef VAORanderMatrixCoordinate_hpp
#define VAORanderMatrixCoordinate_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"
#include <iostream>

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

class VAORanderMatrixCoordinate : public VAORander {
private:
    GLuint _VAO;
    GLuint _texture1;
    GLuint _texture2;
    glm::vec3 _cubePositions[10];
public:
    void createVAO();
    void beforeRander(GLuint program);
    void rander(GLuint program);
    
    GLuint createTexture(char const * path, GLuint pixelFormat, GLint param);
};

#endif /* VAORanderMatrixCoordinate_hpp */
