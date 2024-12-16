//
//  YZKContrastRender.m
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/12/13.
//

#import "YZKContrastRender.h"
#import "YZKTextureManager.h"

@interface YZKContrastRender ()
@property (nonatomic, weak) EAGLContext *context;
@property (nonatomic, assign) GLuint VAO;
@property (nonatomic, assign) GLuint VBO;
@property (nonatomic, assign) GLuint EBO;
@property (nonatomic, assign) GLuint pic_texture;

@end

@implementation YZKContrastRender

/*
对比度是画面黑与白的比值，也就是从黑到白的渐变层次。比值越大，从黑到白的渐变层次就越多，从而色彩表现越丰富。
对比度对视觉效果的影响非常关键，一般来说对比度越大，图像越清晰醒目，色彩也越鲜明艳丽；而对比度小，则会让整个画面都灰蒙蒙的。
简单的说，对比度是像素颜色和某个中值的差，它可以让明亮的颜色更明亮，让灰暗的颜色更灰暗。

这里实现个简单的线性对比度算法：
结果=中值差*对比度+中值
*/

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.vertexShaderName = @"contrast";
        self.fragmentShaderName = @"contrast";
    }
    return self;
}


- (void)renderWithContext:(EAGLContext *)context
{
    self.context = context;
    float verData[] = {
        // 位置             纹理坐标
        1.0f,1.0f,0.0f,     1.0f,1.0f,
        1.0f,-1.0f,0.0f,    1.0f,0.0f,
        -1.0f,-1.0f,0.0f,   0.0f,0.0f,
        -1.0f,1.0f,0.0f,    0.0f,1.0f,
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLuint pic_texture = [YZKTextureManager createTexture:[[NSBundle mainBundle] pathForResource:@"nature" ofType:@"jpg"] textureWrapMode:GL_REPEAT];
    
    glUseProgram(self.glprogram);
    
    glUniform1i(glGetUniformLocation(self.glprogram, "pic_texture"), 0); // 手动设置, 采样器（即uniform变量texture1）绑定的是纹理单元0
    
    glUniform1f(glGetUniformLocation(self.glprogram, "slider_value"), 1.0); // 手动设置

    //激活纹理单元，接下来的 glBindTexture 函数调用会绑定纹理到当前激活的纹理单元
    glActiveTexture(GL_TEXTURE0);
    // 将纹理绑定到当前激活的纹理单元，即纹理单元0。因为前面已经将采样器 texture1 和当前纹理单元绑定，所以采样器 texture1 可以获取到纹理 _texture1。
    glBindTexture(GL_TEXTURE_2D, pic_texture);

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //设置gl渲染窗口大小
    glViewport(0, 0, self.size.width, self.size.height);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //EACAGLContext 渲染OpenGL绘制好的图像到EACAGLLayer
    [context presentRenderbuffer:GL_RENDERBUFFER];
    
    self.VAO = VAO;
    self.VBO = VBO;
    self.EBO = EBO;
    self.pic_texture = pic_texture;
}

- (void)stopRender
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
    glDeleteTextures(1, &_pic_texture);
    glDeleteProgram(self.glprogram);
}

- (void)sliderValueChanged:(CGFloat)value
{    
    glUseProgram(self.glprogram);
    int valueLocation = glGetUniformLocation(self.glprogram, "slider_value");
    glUniform1f(valueLocation, value);
        
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, self.size.width, self.size.height);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //EACAGLContext 渲染OpenGL绘制好的图像到EACAGLLayer
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}



@end
