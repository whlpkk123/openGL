//
//  YZKSaturationRender.m
//  OpenGLESDemo
//
//

#import "YZKSaturationRender.h"

/*
 饱和度可定义为彩度除以明度，与彩度同样表征彩色偏离同亮度灰色的程度。饱和度是指色彩的鲜艳程度，也称色彩的纯度。
 饱和度取决于该色中含色成分和消色成分（灰色）的比例。含色成分越大，饱和度越大；消色成分越大，饱和度越小。
 纯的颜色都是高度饱和的，如鲜红，鲜绿。混杂上白色，灰色或其他色调的颜色，是不饱和的颜色，如绛紫，粉红，黄褐等。完全不饱和的颜色根本没有色调，如黑白之间的各种灰色。
 简单的说，饱和度就是每个像素色彩本身的鲜艳程度，饱和度越低越接近灰色，越高就越鲜艳。
 
 先根据亮度比例计算出灰度值，用灰度值与原色通过饱和度混合就可以得到新的颜色了。
 */

@implementation YZKSaturationRender

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.vertexShaderName = @"contrast";
        self.fragmentShaderName = @"saturation";
    }
    return self;
}


@end
