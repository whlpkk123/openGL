//
//  Model.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/23.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <iostream>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:
    /*  函数   */
    Model(const char *path);
    void Draw(Shader shader);
private:
    /*  模型数据  */
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    std::string directory;
    /*  函数   */
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif /* Model_hpp */
