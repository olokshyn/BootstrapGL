//
// Created by oleg on 16.02.18.
//

#ifndef SHADERS_APPCONTEXT_HPP
#define SHADERS_APPCONTEXT_HPP

#include <functional>

#include "GLFWLibHandle.hpp"
#include "WindowHandle.hpp"
#include "Camera.hpp"

namespace BootstrapGL
{

class AppContext
{
public:
    typedef std::function<void(GLFWwindow* window,
                               int key, int scancode,
                               int action, int mods,
                               float delta_time)>
            key_handler_t;
    typedef std::function<void(GLFWwindow* window,
                               double xpos,
                               double ypos)>
            mouse_handler_t;
    typedef std::function<void(GLFWwindow* window,
                               double xoffset,
                               double yoffset)>
            scroll_handler_t;

public:
    static AppContext& CreateContext(int window_width = 0,
                                     int window_height = 0,
                                     const std::string& window_title = "",
                                     bool register_key_callback = true,
                                     bool register_mouse_callback = true);

public:
    GLFWwindow* window();

    void set_key_handler(key_handler_t key_handler);
    void set_mouse_handler(mouse_handler_t mouse_handler);

    Camera& camera();

    void main_loop(const std::function<bool(GLFWwindow*, float delta_time)>& render_func = {});

private:
    static void key_handler_callback(GLFWwindow* window,
                                     int key, int scancode,
                                     int action, int mods);
    static void mouse_handler_callback(GLFWwindow* window,
                                       double xpos, double ypos);
    static void scroll_handler_callback(GLFWwindow* window,
                                        double xoffset, double yoffset);
    static void framebuffer_size_callback(GLFWwindow* window,
                                          int width, int height);

private:
    AppContext(int window_width,
               int window_height,
               const std::string& window_title,
               bool register_key_callback = true,
               bool register_mouse_callback = true,
               bool register_scroll_callback = true);

private:
    GLFWLibHandle m_lib_handle;
    WindowHandle m_window;
    key_handler_t m_key_handler;
    mouse_handler_t m_mouse_handler;
    scroll_handler_t m_scroll_handler;
    Camera m_camera;
    float m_last_frame_time;
    float m_delta_time;
    float m_last_mouse_pos_x;
    float m_last_mouse_pos_y;
    bool m_first_mouse_move;
};

}

#endif //SHADERS_APPCONTEXT_HPP
