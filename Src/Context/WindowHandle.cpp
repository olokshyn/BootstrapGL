//
// Created by oleg on 16.02.18.
//

#include "WindowHandle.hpp"

using namespace BootstrapGL;

WindowHandle::~WindowHandle()
{
    glfwDestroyWindow(m_window);
}
