//
//  FragmentShader.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/8.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef FragmentShader_hpp
#define FragmentShader_hpp

#include <OpenGL/gltypes.h>
#import <Foundation/Foundation.h>

class FragmentShader {
    
public:
    GLuint createShader(NSString *path);
};

#endif /* FragmentShader_hpp */
