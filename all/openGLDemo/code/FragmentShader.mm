//
//  FragmentShader.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/8.
//

#include "FragmentShader.hpp"
#include "glad.h"

#include <iostream>

GLuint FragmentShader:: createShader(NSString *path) {
    
    NSString *fragShaderString = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    const GLchar *fragShaderSource = fragShaderString.UTF8String;
    if (fragShaderSource == NULL) {
        std::cout << "ERROR path 路径不对，需要设置工作目录" << std::endl;
        exit(EXIT_FAILURE);
    }

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);
    
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR 片段着色器\n" << infoLog << std::endl;
    }
    
    return fragShader;
}
