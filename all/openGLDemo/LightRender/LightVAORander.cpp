//
//  LightVAORander.cpp
//  openGLDemo
//
//  Created by YZK on 2018/4/10.
//

#include "LightVAORander.hpp"

void LightVAORander:: beforeRander(GLuint program, GLuint lightProgram) {
}

void LightVAORander::processInputEvent(GLFWwindow *window, int key, int scanCode, int action, int mods) {
}

void LightVAORander::handleWindow(GLFWwindow *window) {
}



void LightVAORander::setBool(GLuint program, const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void LightVAORander::setInt(GLuint program, const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void LightVAORander::setFloat(GLuint program, const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void LightVAORander::setVec2(GLuint program, const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void LightVAORander::setVec2(GLuint program, const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void LightVAORander::setVec3(GLuint program, const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void LightVAORander::setVec3(GLuint program, const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void LightVAORander::setVec4(GLuint program, const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void LightVAORander::setVec4(GLuint program, const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void LightVAORander::setMat2(GLuint program, const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void LightVAORander::setMat3(GLuint program, const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void LightVAORander::setMat4(GLuint program, const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
