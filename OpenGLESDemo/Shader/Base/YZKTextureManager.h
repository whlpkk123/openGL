//
//  YZKTextureManager.h
//  OpenGLESDemo
//
//

#import <Foundation/Foundation.h>
#import <OpenGLES/gltypes.h>

NS_ASSUME_NONNULL_BEGIN

@interface YZKTextureManager : NSObject

+ (GLuint)createTexture:(NSString *)imagePath textureWrapMode:(GLint)textureWrapMode;
+ (GLuint)createTexture2:(NSString *)imagePath textureWrapMode:(GLint)textureWrapMode;

@end

NS_ASSUME_NONNULL_END
