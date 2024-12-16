//
//  YZKGLView.m
//  OpenGLESDemo
//
//

#import "YZKGLView.h"

@interface YZKGLView ()
{
    GLuint _renderBuffer;
    GLuint _framebuffer;
}

@property (nonatomic, strong) CAEAGLLayer *eaglLayer;

@end

@implementation YZKGLView

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self prepareLayer];
        [self prepareContext];
        [self prepareRenderBuffer];
        [self prepareFrameBuffer];
    }
    return self;
}

- (void)dealloc
{
    glDeleteRenderbuffers(1, &_renderBuffer);
    glDeleteFramebuffers(1, &_framebuffer);
}

- (void)prepareLayer
{
    self.eaglLayer = (CAEAGLLayer *)self.layer;
    //设置不透明，节省性能
    self.eaglLayer.opaque = YES;
}

- (void)prepareContext
{
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    [EAGLContext setCurrentContext:self.context];
}

- (void)prepareRenderBuffer
{
    glGenRenderbuffers(1, &_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
    //调用这个方法来创建一块空间用于存储缓冲数据，替代了glRenderbufferStorage
    [self.context renderbufferStorage:GL_RENDERBUFFER fromDrawable:self.eaglLayer];
}

- (void)prepareFrameBuffer
{
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    //附加之前的_renderBuffer
    //GL_COLOR_ATTACHMENT0指定第一个颜色缓冲区附着点
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _renderBuffer);
}

@end
