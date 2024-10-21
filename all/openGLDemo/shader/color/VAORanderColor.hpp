//
//  VAORanderColor.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef VAORanderColor_hpp
#define VAORanderColor_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"

class VAORanderColor : public VAORander {
private:
    GLuint _VAO;
public:
    void createVAO();
    void rander(GLuint program);
};

#endif /* VAORanderColor_hpp */
