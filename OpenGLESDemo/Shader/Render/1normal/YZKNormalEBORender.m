//
//  YZKNormalEBORender.m
//  OpenGLESDemo
//
//

#import "YZKNormalEBORender.h"

@implementation YZKNormalEBORender

- (void)renderWithContext:(EAGLContext *)context
{
    float vertices[] = {
        1.0f, 1.0f, 0.0f,   // 右上角
        1.0f, -1.0f, 0.0f,  // 右下角
        -1.0f, 1.0f, 0.0f,  // 左上角
        -1.0f, -1.0f, 0.0f, // 左下角
    };

    const GLint Indices[] = {
        0, 1, 2,
        2, 3, 1
    };
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //顶点坐标对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将顶点坐标写入顶点VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //告诉OpenGL该如何解析顶点数据
    
    //shader中vertexPosition参数的索引，因为是只有一个参数，所以是0，也可以使用glGetAttribLocation函数，传入_glprogrem和参数名称字符串查找
    int vertexPositionIndex = 0;
    //每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVetexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。由于在调用glVetexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。
    glVertexAttribPointer(vertexPositionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    //启用attribute变量，使其对GPU可见，默认为关闭
    glEnableVertexAttribArray(vertexPositionIndex);

    //索引
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    //将顶点索引数据写入索引缓冲对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    
    //选择程序对象为当前使用的程序，类似setCurrentContext
    glUseProgram(self.glprogram);
    
    //清屏为白色
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //设置gl渲染窗口大小
    glViewport(0, 0, self.size.width, self.size.height);
    
    /*
     第一个参数指定了我们绘制的模式，这个和glDrawArrays的一样。
     第二个参数是我们打算绘制顶点的个数，这里填6，也就是说我们一共需要绘制6个顶点。
     第三个参数是索引的类型，这里是GL_UNSIGNED_INT。
     最后一个参数里我们可以指定EBO中的偏移量（或者传递一个索引数组，但是这是当你不在使用索引缓冲对象的时候），我们会在这里填写0。
     */
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //EACAGLContext 渲染OpenGL绘制好的图像到EACAGLLayer
    [context presentRenderbuffer:GL_RENDERBUFFER];
    
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(self.glprogram);
}


@end
