//
//  VAORanderColorTwoTriangle.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef VAORanderColorTwoTriangle_hpp
#define VAORanderColorTwoTriangle_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"

class VAORanderColorTwoTriangle : public VAORander {
private:
    GLuint _VAO;
public:
    void createVAO();
    void rander(GLuint program);
};

#endif /* VAORanderColorTwoTriangle_hpp */
