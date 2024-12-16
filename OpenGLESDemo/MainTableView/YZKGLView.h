//
//  YZKGLView.h
//  OpenGLESDemo
//
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES3/gl.h>
#import "YZKRender.h"

NS_ASSUME_NONNULL_BEGIN

@interface YZKGLView : UIView

@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, strong) YZKRender *render;

@end

NS_ASSUME_NONNULL_END
