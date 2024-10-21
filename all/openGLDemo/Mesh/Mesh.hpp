//
//  Mesh.hpp
//  openGLDemo
//
//  Created by YZK on 2018/4/23.
//  Copyright © 2018年 xindong. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include <vector>
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

#include "Shader.hpp"

using namespace std;

//顶点数据结构
struct Vertex {
    glm::vec3 Position;   //位置向量
    glm::vec3 Normal;     //法向量
    glm::vec2 TexCoords;  //纹理坐标向量
};

//纹理数据结构
struct Texture {
    unsigned int id;      //纹理id
    string type;          //纹理类型(漫反射贴图或者是镜面光贴图)
    string path;
};


class Mesh {
public:
    /*  网格数据  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    /*  函数  */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader shader);
private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /*  函数  */
    void setupMesh();
};



#endif /* Mesh_hpp */
