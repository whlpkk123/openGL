//
//  YZKUniformColorRender.m
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/10/24.
//

#import "YZKUniformColorRender.h"

@interface YZKUniformColorRender ()
@property (nonatomic, weak) EAGLContext *context;
@property (nonatomic, assign) GLuint VAO;
@property (nonatomic, assign) GLuint VBO;

@property (nonatomic, strong) CADisplayLink *displayLink;

@end

@implementation YZKUniformColorRender

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.vertexShaderName = @"uniform";
        self.fragmentShaderName = @"uniform";
    }
    return self;
}

- (void)renderWithContext:(EAGLContext *)context
{
    self.context = context;
    //绘制三角形需要三个坐标，由于是屏幕，所以z的值都为0。OpenGL的坐标系是以中心为原点的，所以（1，1）在右上角
    const float vertices[] = {
        1.0f, 1.0f, 0.0f,   // 右上角
        1.0f, -1.0f, 0.0f,  // 右下角
        -1.0f, -1.0f, 0.0f, // 左下角
    };
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    self.VAO = VAO;
    
    //顶点坐标对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    self.VBO = VBO;
    //将顶点坐标写入顶点VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //告诉OpenGL该如何解析顶点数据
    
    //shader中vertexPosition参数的索引，因为是只有一个参数，所以是0，也可以使用glGetAttribLocation函数，传入_glprogrem和参数名称字符串查找
    int vertexPositionIndex = 0;
    //每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVetexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。由于在调用glVetexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。
    glVertexAttribPointer(vertexPositionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    //启用attribute变量，使其对GPU可见，默认为关闭
    glEnableVertexAttribArray(vertexPositionIndex);


    //选择程序对象为当前使用的程序，类似setCurrentContext
    glUseProgram(self.glprogram);

    int vertexColorLocation = glGetUniformLocation(self.glprogram, "ourColor");
    float timeValue = CACurrentMediaTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    float redValue = (cos(timeValue) / 2.0f) + 0.5f;
    glUniform4f(vertexColorLocation, redValue, greenValue, 1.0-redValue, 1.0f);

    int vertexOffsetLocation = glGetUniformLocation(self.glprogram, "ourOffset");
    glUniform2f(vertexOffsetLocation, greenValue-0.5, redValue-0.5);

    
    //清屏为白色
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //设置gl渲染窗口大小
    glViewport(0, 0, self.size.width, self.size.height);
    //绘制三个顶点的三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //EACAGLContext 渲染OpenGL绘制好的图像到EACAGLLayer
    [context presentRenderbuffer:GL_RENDERBUFFER];
    
    CADisplayLink *link = [CADisplayLink displayLinkWithTarget:self selector:@selector(renderAlways)];
    [link addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    self.displayLink = link;
}

- (void)renderAlways
{
    int vertexColorLocation = glGetUniformLocation(self.glprogram, "ourColor");
    float timeValue = CACurrentMediaTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    float redValue = (cos(timeValue) / 2.0f) + 0.5f;
    glUniform4f(vertexColorLocation, redValue, greenValue, 1.0-redValue, 1.0f);
    
    int vertexOffsetLocation = glGetUniformLocation(self.glprogram, "ourOffset");
    glUniform2f(vertexOffsetLocation, greenValue-0.5, redValue-0.5);

    //清屏为白色
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //设置gl渲染窗口大小
    glViewport(0, 0, self.size.width, self.size.height);
    //绘制三个顶点的三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //EACAGLContext 渲染OpenGL绘制好的图像到EACAGLLayer
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)stopRender
{
    [self.displayLink invalidate];
    self.displayLink = nil;
    
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteProgram(self.glprogram);
}

@end
