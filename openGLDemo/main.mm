//
//  main.cpp
//  openGLDemo
//
//  Created by xindong on 18/1/15.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include <iostream>


#import <Foundation/Foundation.h>
#include "RanderProcess.hpp"
#include "LightRanderProcess.hpp"
//#include "ModelRanderProcess.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



#pragma mark - VAO & shader

#include "VAORanderColor.hpp"
#include "VAORanderColorOther.hpp"

#include "VAORanderTwoTriangle.hpp"
#include "VAORanderTwoTriangleOther.hpp"
#include "VAORanderTwoTriangleThree.hpp"

#include "VAORanderUniform.hpp"
#include "VAORanderUniformOffset.hpp"

#include "VAORanderTextures.hpp"

#include "VAORanderMatrix.hpp"
#include "VAORanderMatrixOther.hpp"

#include "VAORanderMatrixCoordinate.hpp"
#include "VAORanderCamera.hpp"
#include "VAORanderCameraCursor.hpp"

#include "VAORanderLight.hpp"
#include "VAORanderMaterial.hpp"
#include "VAORanderLightingMaps.hpp"
#include "VAORanderLightingCastersDirectionalLight.hpp"
#include "VAORanderLightingCastersPointLight.hpp"
#include "VAORanderLightingCastersSpotlight.hpp"
#include "VAORanderMultipleLight.hpp"


//#include "Model.hpp"

#pragma mark - Declaration

#pragma mark 第一章

void showColor();
void showTwoTriangle();
void showUniform();
void showUniformOffset();
void showTexture();
void showMatrix();
void showMatrixCoordinate();

#pragma mark 第二章

void showLight();  //光照
void showMaterial(); //材质
void showLightingMaps(); //光照贴图
void showLightingCasters(); //投光物
void showMultipleLights(); //多光源

#pragma mark 第三章
void showModel();


#pragma mark - Main

int main(int argc, const char * argv[]) {
    
//    showColor();
    showTwoTriangle();
//    showUniform();
//    showUniformOffset();
//    showTexture();
//    showMatrix();
//    showMatrixCoordinate();
//    showLight();
//    showMaterial();
//    showLightingMaps();
//    showLightingCasters();
//    showMultipleLights();
//    showModel();
    
    return 0;
}

#pragma mark - Implementation

#pragma mark 第一章

void showColor() {
//    VAORander *rander = new VAORanderColor();
    VAORander *rander = new VAORanderColorOther();
    
    RanderProcess randerProcess;
    randerProcess.createRanderProcess(@"color/VertextShader", @"color/FragmentShader", rander);
}

void showTwoTriangle() {
//    VAORander *rander = new VAORanderTwoTriangle();
//    VAORander *rander = new VAORanderTwoTriangleOther();
    VAORander *rander = new VAORanderTwoTriangleThree();

    RanderProcess randerProcess;
    randerProcess.createRanderProcess(@"twoTriangle/VertextShader", @"twoTriangle/FragmentShader", rander);
}

void showUniform() {
    VAORander *rander = new VAORanderUniform();
    RanderProcess randerProcess;
    randerProcess.createRanderProcess(@"uniform/VertextShader", @"uniform/FragmentShader", rander);
}

void showUniformOffset() {
    VAORander *rander = new VAORanderUniformOffset();
    RanderProcess randerProcess;
    randerProcess.createRanderProcess(@"uniformOffset/VertextShader", @"uniformOffset/FragmentShader", rander);
}

void showTexture() {
    VAORander *rander = new VAORanderTextures();
    RanderProcess randerProcess;
    randerProcess.createRanderProcess(@"textures/VertextShader", @"textures/FragmentShader", rander);
}

void showMatrix() {
//    VAORander *rander = new VAORanderMatrix();
    VAORander *rander = new VAORanderMatrixOther();

    RanderProcess randerProcess;
    randerProcess.createRanderProcess(@"matrix/VertextShader", @"matrix/FragmentShader", rander);
}

void showMatrixCoordinate() {
//    VAORander *rander = new VAORanderMatrixCoordinate();
//    VAORander *rander = new VAORanderCamera();
    VAORander *rander = new VAORanderCameraCursor();

    RanderProcess randerProcess;
    randerProcess.createRanderProcess(@"matrixCoordinate/VertextShader", @"matrixCoordinate/FragmentShader", rander);
}

#pragma mark 第二章

void showLight() {
    LightVAORander *rander = new VAORanderLight();
    
    LightRanderProcess randerProcess;
    randerProcess.createLightRanderProcess(@"light/VertextShader", @"light/FragmentShader", @"light/LightVertextShader", @"light/LightFragmentShader", rander);
}

void showMaterial() {
    LightVAORander *rander = new VAORanderMaterial();
    
    LightRanderProcess randerProcess;
    randerProcess.createLightRanderProcess(@"material/VertextShader", @"material/FragmentShader", @"material/LightVertextShader", @"material/LightFragmentShader", rander);
}

void showLightingMaps() {
    LightVAORander *rander = new VAORanderLightingMaps();
    
    LightRanderProcess randerProcess;
    randerProcess.createLightRanderProcess(@"lightingMaps/VertextShader", @"lightingMaps/FragmentShader", @"lightingMaps/LightVertextShader", @"lightingMaps/LightFragmentShader", rander);
}

void showLightingCasters() {
    //平行光
//    LightVAORander *rander = new VAORanderLightingCastersDirectionalLight();
//    LightRanderProcess randerProcess;
//    randerProcess.createLightRanderProcess(@"lightingCasters/DirectionalLight/VertextShader", @"lightingCasters/DirectionalLight/FragmentShader", @"lightingCasters/DirectionalLight/LightVertextShader", @"lightingCasters/DirectionalLight/LightFragmentShader", rander);
    
    //点光源
//    LightVAORander *rander = new VAORanderLightingCastersPointLight();
//    LightRanderProcess randerProcess;
//    randerProcess.createLightRanderProcess(@"lightingCasters/PointLights/VertextShader", @"lightingCasters/PointLights/FragmentShader", @"lightingCasters/PointLights/LightVertextShader", @"lightingCasters/PointLights/LightFragmentShader", rander);
    
    //聚光
    LightVAORander *rander = new VAORanderLightingCastersSpotlight();
    LightRanderProcess randerProcess;
    randerProcess.createLightRanderProcess(@"lightingCasters/Spotlight/VertextShader", @"lightingCasters/Spotlight/FragmentShader", @"lightingCasters/Spotlight/LightVertextShader", @"lightingCasters/Spotlight/LightFragmentShader", rander);
}

void showMultipleLights() {
    LightVAORander *rander = new VAORanderMultipleLight();
    
    LightRanderProcess randerProcess;
    randerProcess.createLightRanderProcess(@"multipleLights/VertextShader", @"multipleLights/FragmentShader", @"multipleLights/LightVertextShader", @"multipleLights/LightFragmentShader", rander);
}

//void showModel() {
//    ModelRanderProcess randerProcess;
//    randerProcess.createModelRanderProcess(@"Resource/nanosuit/shader/VertextShader", @"Resource/nanosuit/shader/FragmentShader", @"Resource/nanosuit/nanosuit.obj");
//}

