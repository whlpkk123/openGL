//
//  ShaderProgram.hpp
//  openGLDemo
//
//  Created by xindong on 2018/3/6.
/**
 着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的版本，然后在渲染对象的时候激活这个着色器程序。已激活着色器程序的着色器将在我们发送渲染调用的时候被使用。
 
 一个VAO存储着多个VAO，而一个VAO存储着多个顶点数据。
 */

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <OpenGL/gltypes.h>

class ShaderProgram {
    
public:
    GLuint linkVertexShader(GLuint vertexShader, GLuint fragmentShader);
};

#endif /* ShaderProgram_hpp */
