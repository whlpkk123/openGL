//
//  stb_image_imp.cpp
//  openGLDemo
//
//  Created by ByteDance on 2024/10/18.
//  Copyright © 2024 xindong. All rights reserved.
//

/*
 stb_image.h是Sean Barrett的一个非常流行的单头文件图像加载库，它能够加载大部分流行的文件格式，并且能够很简单得整合到你的工程之中。
 下载这一个头文件，将它以stb_image.h的名字加入你的工程，通过定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，让其只包含相关的函数定义源码，等于是将这个头文件变为一个 .cpp 文件了。
 */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
