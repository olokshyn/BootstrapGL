//
// Created by oleg on 16.02.18.
//

#ifndef SHADERS_GLFWLIBHANDLE_HPP
#define SHADERS_GLFWLIBHANDLE_HPP

namespace BootstrapGL
{

class GLFWLibHandle
{
public:
    GLFWLibHandle(int version_major = 3, int version_minor = 3);
    ~GLFWLibHandle();

    GLFWLibHandle(const GLFWLibHandle& other) = delete;
    GLFWLibHandle& operator=(const GLFWLibHandle& other) = delete;
};

}

#endif //SHADERS_GLFWLIBHANDLE_HPP
