//
//  VAORanderTwoTriangleOther.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef VAORanderTwoTriangleOther_hpp
#define VAORanderTwoTriangleOther_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"

class VAORanderTwoTriangleOther : public VAORander {
private:
    GLuint _VAO;
public:
    void createVAO();
    void rander(GLuint program);
};

#endif /* VAORanderTwoTriangleOther_hpp */
