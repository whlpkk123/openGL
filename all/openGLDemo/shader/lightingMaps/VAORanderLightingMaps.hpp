//
//  VAORanderLightingMaps.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef VAORanderLightingMaps_hpp
#define VAORanderLightingMaps_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "LightVAORander.hpp"

class VAORanderLightingMaps : public LightVAORander {
private:
    GLuint _VAO;
    GLuint _lightVAO;
    glm::vec3 _lightPos;
    
    GLuint _texture; //漫反射纹理
    GLuint _texture2; //镜面反射纹理
    GLuint _texture3; //放射光纹理
public:
    void createVAO();
    void rander(GLuint program, GLuint lightProgram);
    void beforeRander(GLuint program, GLuint lightProgram);
    
    GLuint createTexture(char const * path, GLint param);
};

#endif /* VAORanderLightingMaps_hpp */
