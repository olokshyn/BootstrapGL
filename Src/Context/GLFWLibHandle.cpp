//
// Created by oleg on 16.02.18.
//

#include "GLFWLibHandle.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace BootstrapGL;

GLFWLibHandle::GLFWLibHandle(int version_major, int version_minor)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWLibHandle::~GLFWLibHandle()
{
    glfwTerminate();
}
