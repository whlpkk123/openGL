//
//  VAORanderTextures.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef VAORanderTextures_hpp
#define VAORanderTextures_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"
#include <iostream>

class VAORanderTextures : public VAORander {
private:
    GLuint _VAO;
    GLuint _texture1;
    GLuint _texture2;
    GLfloat _alpha;
public:
    void createVAO();
    void beforeRander(GLuint program);
    void rander(GLuint program);
    void processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods);
    
    GLuint createTexture(char const * path, GLint param);
};

#endif /* VAORanderTextures_hpp */
