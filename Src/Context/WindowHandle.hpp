//
// Created by oleg on 16.02.18.
//

#ifndef SHADERS_WINDOWHANDLE_HPP
#define SHADERS_WINDOWHANDLE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BootstrapGL
{

class WindowHandle
{
public:
    explicit WindowHandle(GLFWwindow* window = nullptr)
            : m_window(window)
    {}

    ~WindowHandle();

    WindowHandle(const WindowHandle& other) = delete;

    WindowHandle& operator=(const WindowHandle& other) = delete;

    operator const GLFWwindow*() const
    { return m_window; }

    operator GLFWwindow*()
    { return m_window; }

    operator bool()
    { return m_window != nullptr; }

private:
    GLFWwindow* m_window;
};

}

#endif //SHADERS_WINDOWHANDLE_HPP
