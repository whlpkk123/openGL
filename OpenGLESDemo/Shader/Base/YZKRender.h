//
//  YZKRender.h
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/10/24.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/gltypes.h>
#import <OpenGLES/ES3/gl.h>

NS_ASSUME_NONNULL_BEGIN

@interface YZKRender : NSObject

@property (nonatomic, assign) CGSize size;

// for subclass use
@property (nonatomic, assign) GLuint glprogram;
@property (nonatomic, copy) NSString *vertexShaderName;
@property (nonatomic, copy) NSString *fragmentShaderName;

- (void)renderWithContext:(EAGLContext *)context;
- (void)sliderValueChanged:(CGFloat)value;
- (void)stopRender;

// for 外部调用
- (void)prepareProgramWithShader;

@end

NS_ASSUME_NONNULL_END
