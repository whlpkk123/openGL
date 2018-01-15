//
//  ModelRanderProcess.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/24.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef ModelRanderProcess_hpp
#define ModelRanderProcess_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include "Model.hpp"
#include "Shader.hpp"

class ModelRanderProcess {
    
public:
    void createModelRanderProcess(NSString *vertexShaderPath, NSString *fragmentShaderPath, NSString *modelPath);
};

#endif /* ModelRanderProcess_hpp */
