//
//  YZKTextureRender.m
//  OpenGLESDemo
//
//

#import "YZKTextureRender.h"
#import "YZKTextureManager.h"

@implementation YZKTextureRender

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.vertexShaderName = @"texture";
        self.fragmentShaderName = @"texture";
    }
    return self;
}


- (void)renderWithContext:(EAGLContext *)context
{
    float verData[] = {
        // 位置              颜色                 纹理坐标
        0.5f,0.5f,0.0f,     1.0f,0.0f,0.0f,     1.0f,1.0f,
        0.5f,-0.5f,0.0f,    0.0f,1.0f,0.0f,     1.0f,0.0f,
        -0.5f,-0.5f,0.0f,   0.0f,0.0f,1.0f,     0.0f,0.0f,
        -0.5f,0.5f,0.0f,    1.0f,1.0f,0.0f,     0.0f,1.0f,
    };
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };

    GLuint VAO,VBO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(verData), verData, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    GLuint texture1 = [YZKTextureManager createTexture:[[NSBundle mainBundle] pathForResource:@"container" ofType:@"jpg"] textureWrapMode:GL_REPEAT];
    
    GLuint texture2 = [YZKTextureManager createTexture:[[NSBundle mainBundle] pathForResource:@"awesomeface" ofType:@"png"] textureWrapMode:GL_CLAMP_TO_EDGE];

    glUseProgram(self.glprogram);
    
    glUniform1i(glGetUniformLocation(self.glprogram, "texture1"), 0); // 手动设置, 采样器（即uniform变量texture1）绑定的是纹理单元0
    glUniform1i(glGetUniformLocation(self.glprogram, "texture2"), 1); // 手动设置, 采样器（即uniform变量texture2）绑定的是纹理单元1

    glUniform1f(glGetUniformLocation(self.glprogram, "alpha"), 1.0); // 手动设置
    
    //激活纹理单元，接下来的 glBindTexture 函数调用会绑定纹理到当前激活的纹理单元
    glActiveTexture(GL_TEXTURE0);
    // 将纹理绑定到当前激活的纹理单元，即纹理单元0。因为前面已经将采样器 texture1 和当前纹理单元绑定，所以采样器 texture1 可以获取到纹理 _texture1。
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2); // 原理同上，采样器 texture2 可以获取到纹理 _texture2。

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //设置gl渲染窗口大小
    glViewport(0, 0, self.size.width, self.size.height);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //EACAGLContext 渲染OpenGL绘制好的图像到EACAGLLayer
    [context presentRenderbuffer:GL_RENDERBUFFER];
    
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    glDeleteProgram(self.glprogram);
}


@end
