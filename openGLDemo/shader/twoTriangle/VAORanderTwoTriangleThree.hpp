//
//  VAORanderTwoTriangleThree.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef VAORanderTwoTriangleThree_hpp
#define VAORanderTwoTriangleThree_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"

class VAORanderTwoTriangleThree : public VAORander {
private:
    GLuint _VAO;
public:
    void createVAO();
    void rander(GLuint program);
};

#endif /* VAORanderTwoTriangleThree_hpp */