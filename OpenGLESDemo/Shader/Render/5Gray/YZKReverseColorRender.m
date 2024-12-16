//
//  YZKReverseColorRender.m
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/12/13.
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
