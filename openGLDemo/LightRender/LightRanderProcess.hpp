//
//  Rander.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef LightRanderProcess_hpp
#define LightRanderProcess_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#import <Foundation/Foundation.h>
#include "LightVAORander.hpp"

class LightRanderProcess {
    
public:
    void createLightRanderProcess(NSString *vertexShaderPath, NSString *fragmentShaderPath, NSString *lightVertexShaderPath, NSString *lightFragmentShaderPath,LightVAORander *rander);
};

#endif /* LightRanderProcess_hpp */
