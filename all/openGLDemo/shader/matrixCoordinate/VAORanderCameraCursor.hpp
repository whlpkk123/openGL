//
//  VAORanderCameraCursor.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef VAORanderCameraCursor_hpp
#define VAORanderCameraCursor_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "VAORander.hpp"
#include <iostream>

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

class VAORanderCameraCursor : public VAORander {
private:
    GLuint _VAO;
    GLuint _texture1;
    GLuint _texture2;
    glm::vec3 _cubePositions[10];
    
public:
    void createVAO();
    void beforeRander(GLuint program);
    void rander(GLuint program);
    void processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods);
    void handleWindow(GLFWwindow *window);

    GLuint createTexture(char const * path, GLuint pixelFormat, GLint param);
};

#endif /* VAORanderCameraCursor_hpp */
