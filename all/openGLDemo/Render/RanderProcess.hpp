//
//  Rander.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#ifndef RanderProcess_hpp
#define RanderProcess_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#import <Foundation/Foundation.h>
#include "VAORander.hpp"

class RanderProcess {
    
public:
    void createRanderProcess(NSString *vertexShaderPath, NSString *fragmentShaderPath, VAORander *rander);
};

#endif /* RanderProcess_hpp */
