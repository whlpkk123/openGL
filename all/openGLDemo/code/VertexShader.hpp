//
//  VertexShader.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/8.
//

#ifndef VertexShader_hpp
#define VertexShader_hpp

#include <OpenGL/gltypes.h>
#import <Foundation/Foundation.h>

class VertexShader {
    
public:
    GLuint createShader(NSString *path);
};

#endif /* VertexShader_hpp */
