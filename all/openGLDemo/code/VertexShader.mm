//
//  VertexShader.mm
//  openGLDemo
//
//  Created by YZK on 2018/4/8.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VertexShader.hpp"
#include "glad.h"

#include <iostream>

GLuint VertexShader:: createShader(NSString *path) {
    
    /*
     这里注意，一定要设置 scheme -> option -> working directory，设置工作目录为 $(PROJECT_DIR)/openGLDemo/shader 。要不然路径不对
     */
    NSString *vertexString = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    const GLchar *vertexShaderSource = vertexString.UTF8String;
    if (vertexShaderSource == NULL) {
        std::cout << "ERROR path 路径不对，需要设置工作目录" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // 创建着色器ID引用，着色器类型以参数形式提供给glCreateShader。创建顶点着色器，传递的参数是GL_VERTEX_SHADER。
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译着色器
    glCompileShader(vertexShader);
    
    /*
     首先我们定义一个整型变量来表示是否成功编译，还定义了一个储存错误消息（如果有的话）的容器。然后我们用glGetShaderiv检查是否编译成功。
     如果编译失败，我们会用glGetShaderInfoLog获取错误消息，然后打印它。
     */
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR 顶点着色器\n" << infoLog << std::endl;
    }
    
    return vertexShader;
}
