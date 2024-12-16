//
//  YZKTextureManager.m
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/10/25.
//

#import "YZKTextureManager.h"
#import <OpenGLES/ES3/gl.h>
#import <UIKit/UIKit.h>
#include "stb_image.h"

@implementation YZKTextureManager

+ (GLuint)createTexture:(NSString *)imagePath textureWrapMode:(GLint)textureWrapMode
{
    // 创建纹理的引用
    GLuint texture;
    glGenTextures(1, &texture);
    // 绑定2D纹理目标
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // 设置纹理对象环绕方式
    // glTexParameter*函数对单独的一个坐标轴设置, s轴、t轴、z轴 对应 x、y、z
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapMode);
    
    /*
     设置纹理对象过滤方式
     纹理坐标不依赖于分辨率(Resolution)，它可以是任意浮点值，所以OpenGL需要知道怎样将纹理像素(Texture Pixel)映射到纹理坐标。
     当你有一个很大的物体但是纹理的分辨率很低的时候这就变得很重要了。纹理过滤有很多个选项，我们只讨论最重要的两种：
     GL_NEAREST（也叫邻近过滤，Nearest Neighbor Filtering）是OpenGL默认的纹理过滤方式。当设置为GL_NEAREST的时候，OpenGL会选择中心点最接近纹理坐标的那个像素。
     GL_LINEAR（也叫线性过滤，(Bi)linear Filtering）它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //当纹理被缩小(Minify)时，使用临近过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //当纹理被放大(Magnify)时，使用线性过滤
    
    // 加载并生成纹理
    int width, height, nrChannels;
    // OpenGL要求y轴0.0坐标是在图片的坐下角的，但是图片的y轴0.0坐标通常在左上角。所以这里需要调用 stbi_set_flip_vertically_on_load 函数帮我们翻转y轴
    stbi_set_flip_vertically_on_load(true);
    // 它需要三个int作为它的第二、第三和第四个参数，stb_image.h将会用图像的宽度、高度和颜色通道个数填充这三个变量。
    int alignment = 1;
    
    /*
     iPhone这里需要注意，需要添加stbi_convert_iphone_png_to_rgb(1)函数调用。
     Xcode for iOS by default converts all PNG images to a non-standard iOS-specific PNG derivative. This format saves iOS devices a trivial conversion step during loading, because it uses premultiplied BGRA instead of RGBA color space.
     解决办法：在调用stbi_load函数之前调用stbi_convert_iphone_png_to_rgb(1);
     */
    stbi_convert_iphone_png_to_rgb(1);
    unsigned char *data = stbi_load(imagePath.UTF8String, &width, &height, &nrChannels, 0);
    if (data) {
        //根据颜色通道处理纹理格式
        GLenum format = 0;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4) {
            format = GL_RGBA;
            alignment = 4;
        }
        
        // 设置像素字节对齐数，默认4字节
        glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
        
        /*
         载入图片数据，生成纹理。
         第一个参数指定了纹理目标(Target)。设置为 GL_TEXTURE_2D 意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到 GL_TEXTURE_1D 和 GL_TEXTURE_3D 的纹理不会受到影响）。
         第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
         第三个参数告诉OpenGL我们希望把纹理储存为何种格式。这里我们使用和原图同样的格式。
         第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
         第六个参数应该总是被设为0（历史遗留的问题）。
         第七个参数定义原图的颜色格式，这里使用颜色通道判断，
         第八个参数定义了源图的数据类型。这里是字节流，即char(byte)数组，我们传入对应值 GL_UNSIGNED_BYTE。
         最后一个参数是图像数据。
         */
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); //启用多级渐远纹理
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    else {
        NSLog(@"Failed to load texture");
    }
    // 生成纹理后，可以释放图片的内存
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

+ (GLuint)createTexture2:(NSString *)imagePath textureWrapMode:(GLint)textureWrapMode
{
    // 创建纹理的引用
    GLuint texture;
    glGenTextures(1, &texture);
    // 绑定2D纹理目标
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // 设置纹理对象环绕方式
    // glTexParameter*函数对单独的一个坐标轴设置, s轴、t轴、z轴 对应 x、y、z
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapMode);
    
    /*
     设置纹理对象过滤方式
     纹理坐标不依赖于分辨率(Resolution)，它可以是任意浮点值，所以OpenGL需要知道怎样将纹理像素(Texture Pixel)映射到纹理坐标。
     当你有一个很大的物体但是纹理的分辨率很低的时候这就变得很重要了。纹理过滤有很多个选项，我们只讨论最重要的两种：
     GL_NEAREST（也叫邻近过滤，Nearest Neighbor Filtering）是OpenGL默认的纹理过滤方式。当设置为GL_NEAREST的时候，OpenGL会选择中心点最接近纹理坐标的那个像素。
     GL_LINEAR（也叫线性过滤，(Bi)linear Filtering）它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //当纹理被缩小(Minify)时，使用临近过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //当纹理被放大(Magnify)时，使用线性过滤
    
    // 加载并生成纹理
    UIImage *image = [UIImage imageWithContentsOfFile:imagePath];
    CGImageRef cgImageRef = [image CGImage];
    GLuint width = (GLuint)CGImageGetWidth(cgImageRef);
    GLuint height = (GLuint)CGImageGetHeight(cgImageRef);
    CGRect rect = CGRectMake(0, 0, width, height);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc(width * height * 4);
    CGContextRef context = CGBitmapContextCreate(imageData, width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);

    // OpenGL要求y轴0.0坐标是在图片的坐下角的，但是图片的y轴0.0坐标通常在左上角。所以这里需要调用 stbi_set_flip_vertically_on_load 函数帮我们翻转y轴
    CGContextTranslateCTM(context, 0, height);
    CGContextScaleCTM(context, 1.0, -1.0);
    CGColorSpaceRelease(colorSpace);
    CGContextDrawImage(context, rect, cgImageRef);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D); //启用多级渐远纹理

    // 生成纹理后，可以释放图片的内存
    CGContextRelease(context);
    free(imageData);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}


@end
