//
//  YZKRender.m
//  OpenGLESDemo
//
//

#import "YZKRender.h"

@interface YZKRender ()
@end

@implementation YZKRender

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.vertexShaderName = @"normal";
        self.fragmentShaderName = @"normal";
    }
    return self;
}

- (void)prepareProgramWithShader
{
    //创建顶点着色器
    GLuint vertexShader = [self p_createGLShader:self.vertexShaderName type:GL_VERTEX_SHADER];
    //创建片元着色器
    GLuint fragmentShader = [self p_createGLShader:self.fragmentShaderName type:GL_FRAGMENT_SHADER];

    if (vertexShader == -1 || fragmentShader == -1) {
        return;
    }

    //创建glprogram
    GLuint glprogram = glCreateProgram();
    
    //将程序对象和 着色器对象链接，在ES 3.0中,每个程序对象 必须连接一个顶点着色器和片段着色器
    glAttachShader(glprogram, vertexShader);
    glAttachShader(glprogram, fragmentShader);
    
    //链接程序对象 生成可执行程序(在着色器已完成编译 且程序对象连接了着色器)
    //链接程序会检查各种对象的数量,和各种条件.
    //在链接阶段就是生成最终硬件指令的时候(和C语言一样)
    glLinkProgram(glprogram);
    [self p_checkLinkProgromSuccess:glprogram];

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    self.glprogram = glprogram;
}

- (void)renderWithContext:(EAGLContext *)context
{
}

- (void)stopRender
{
}

- (void)sliderValueChanged:(CGFloat)value
{
}


- (GLuint)p_createGLShader:(NSString *)shaderFileName type:(GLenum)type
{
    GLuint shader = glCreateShader(type);
    NSString *shaderFilePath = [[NSBundle mainBundle] pathForResource:shaderFileName ofType:(type==GL_VERTEX_SHADER?@"vs":@"fs")];
    NSString *shaderString = [NSString stringWithContentsOfFile:shaderFilePath encoding:NSUTF8StringEncoding error:nil];
    const GLchar *shaderSource = shaderString.UTF8String;
    GLint shaderLength = (GLint)[shaderString length];
    //读取shader字符串
    glShaderSource(shader, 1, &shaderSource, &shaderLength);
    //编译shader
    glCompileShader(shader);
    if (![self p_checkCompileShaderSuccess:shader]) {
        return -1;
    }
    return shader;
}

- (BOOL)p_checkCompileShaderSuccess:(GLuint)shader
{
    int compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = (char *)malloc(sizeof(char) * infoLen);
            if (infoLog) {
                //检索信息日志
                //参数: shader 着色器对象句柄
                //      maxLength 保存信息日志的缓冲区大小
                //      length 写入信息日志长度 ,不需要知道可传NULL
                //      infoLog 保存日志信息的指针
                glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
                NSLog(@"Error compiling shader: %s\n", infoLog);
                free(infoLog);
            }
        }
        //删除着色器对象, 参数shader为要删除的着色器对象的句柄
        //若一个着色器链接到一个程序对象,那么该方法不会立刻删除着色器,而是将着色器标记为删除,当着色器不在连接到任何程序对象时,它的内存将被释放.
        glDeleteShader(shader);
        return NO;
    }
    return YES;
}

- (BOOL)p_checkLinkProgromSuccess:(GLuint)program
{
    //检查链接是否成功
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    
    if (!success) {
        GLint infoLen;
        //使用 GL_INFO_LOG_LENGTH 表示获取信息日志
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            GLchar *infoText = (GLchar *)malloc(sizeof(GLchar)*infoLen + 1);
            if (infoText) {
                memset(infoText, 0x00, sizeof(GLchar)*infoLen + 1);

                // 从信息日志中获取信息
                glGetProgramInfoLog(program, infoLen, NULL, infoText);
                NSLog(@"%s", infoText);
                free(infoText);
            }
        }
        //删除程序对象
        glDeleteProgram(program);
        return NO;
    }
    return YES;
}



@end
