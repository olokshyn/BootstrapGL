//
// Created by oleg on 16.02.18.
//

#include "AppContext.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CAPTURE_MOUSE 1

using namespace BootstrapGL;

AppContext& AppContext::CreateContext(int window_width,
                                      int window_height,
                                      const std::string& window_title,
                                      bool register_key_callback,
                                      bool register_mouse_callback)
{
    static AppContext app_context(window_width, window_height, window_title);
    return app_context;
}

GLFWwindow* AppContext::window()
{
    return m_window;
}

void AppContext::set_key_handler(key_handler_t key_handler)
{
    m_key_handler = std::move(key_handler);
}

void AppContext::set_mouse_handler(mouse_handler_t mouse_handler)
{
    m_mouse_handler = std::move(mouse_handler);
}

Camera& AppContext::camera()
{
    return m_camera;
}

void AppContext::main_loop(const std::function<bool(GLFWwindow*, float delta_time)>& render_func)
{
    m_delta_time = 0.0f;
    bool continue_main_loop = true;
    while (!glfwWindowShouldClose(m_window) && continue_main_loop)
    {
        float current_frame = static_cast<float>(glfwGetTime());
        m_delta_time = current_frame - m_last_frame_time;
        m_last_frame_time = current_frame;

        if (render_func)
        {
            continue_main_loop = render_func(m_window, m_delta_time);
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void AppContext::key_handler_callback(GLFWwindow* window,
                                      int key, int scancode,
                                      int action, int mods)
{
    auto& app_context = CreateContext();

    app_context.m_camera.process_keyboard_move(key, app_context.m_delta_time);

    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (app_context.m_key_handler)
    {
        app_context.m_key_handler(window, key, scancode,
                                  action, mods, app_context.m_delta_time);
    }
}

void AppContext::mouse_handler_callback(GLFWwindow* window,
                                        double xpos, double ypos)
{
    auto& app_context = CreateContext();

    if (app_context.m_first_mouse_move)
    {
        app_context.m_last_mouse_pos_x = static_cast<float>(xpos);
        app_context.m_last_mouse_pos_y = static_cast<float>(ypos);
        app_context.m_first_mouse_move = false;
    }

    float xoffset = static_cast<float>(xpos)
                    - app_context.m_last_mouse_pos_x;
    // reversed since y-coordinates go from bottom to top
    float yoffset = app_context.m_last_mouse_pos_y
                    - static_cast<float>(ypos);
    app_context.m_last_mouse_pos_x = static_cast<float>(xpos);
    app_context.m_last_mouse_pos_y = static_cast<float>(ypos);

    app_context.m_camera.process_mouse_move(xoffset, yoffset);

    if (app_context.m_mouse_handler)
    {
        app_context.m_mouse_handler(window, xpos, ypos);
    }
}

void AppContext::scroll_handler_callback(GLFWwindow* window,
                                         double xoffset, double yoffset)
{
    auto& app_context = CreateContext();

    app_context.m_camera.process_mouse_scroll(static_cast<float>(yoffset));

    if (app_context.m_scroll_handler)
    {
        app_context.m_scroll_handler(app_context.m_window,
                                     xoffset, yoffset);
    }
}

void AppContext::framebuffer_size_callback(GLFWwindow* window,
                                           int width, int height)
{
    glViewport(0, 0, width, height);
}

AppContext::AppContext(int window_width, int window_height,
                       const std::string& window_title,
                       bool register_key_callback,
                       bool register_mouse_callback,
                       bool register_scroll_callback)
        : m_window(glfwCreateWindow(window_width,
                                    window_height,
                                    window_title.c_str(),
                                    nullptr, nullptr)),
          m_last_frame_time(0.0f),
          m_delta_time(0.0f),
          m_last_mouse_pos_x(0.0f),
          m_last_mouse_pos_y(0.0f),
          m_first_mouse_move(true)
{
    if (!m_window)
    {
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_window);
    if (register_key_callback)
    {
        glfwSetKeyCallback(m_window, &AppContext::key_handler_callback);
    }
    if (register_mouse_callback)
    {
        glfwSetCursorPosCallback(m_window, &AppContext::mouse_handler_callback);
#if defined(CAPTURE_MOUSE) && CAPTURE_MOUSE
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
    }
    if (register_scroll_callback)
    {
        glfwSetScrollCallback(m_window, &AppContext::scroll_handler_callback);
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(m_window, &AppContext::framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
}
