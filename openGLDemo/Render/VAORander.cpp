//
//  VAORander.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//  Copyright © 2018年 xindong. All rights reserved.
//

#include "VAORander.hpp"

void VAORander:: beforeRander(GLuint program) {
}

void VAORander::processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods) {
}

void VAORander::handleWindow(GLFWwindow *window) {
}



void VAORander::setBool(GLuint program, const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void VAORander::setInt(GLuint program, const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void VAORander::setFloat(GLuint program, const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void VAORander::setVec2(GLuint program, const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void VAORander::setVec2(GLuint program, const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void VAORander::setVec3(GLuint program, const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void VAORander::setVec3(GLuint program, const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void VAORander::setVec4(GLuint program, const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void VAORander::setVec4(GLuint program, const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void VAORander::setMat2(GLuint program, const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void VAORander::setMat3(GLuint program, const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void VAORander::setMat4(GLuint program, const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
