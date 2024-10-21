//
//  VAORanderTwoTriangle.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef VAORanderTwoTriangle_hpp
#define VAORanderTwoTriangle_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"

class VAORanderTwoTriangle : public VAORander {
private:
    GLuint _VAOs[2];
public:
    void createVAO();
    void rander(GLuint program);
};

#endif /* VAORanderTwoTriangle_hpp */
