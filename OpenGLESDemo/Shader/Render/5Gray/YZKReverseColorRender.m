//
//  YZKReverseColorRender.m
//  OpenGLESDemo
//
//

#import "YZKReverseColorRender.h"

@implementation YZKReverseColorRender

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.vertexShaderName = @"gray";
        self.fragmentShaderName = @"reverse_color";
    }
    return self;
}


@end
