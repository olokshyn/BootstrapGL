#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BootstrapGL/Context/AppContext.hpp"

using namespace BootstrapGL;

int main()
{
    try
    {
        const size_t screen_width = 1360;
        const size_t screen_height = 768;

        auto& app_context = AppContext::CreateContext(screen_width,
                                                      screen_height,
                                                      "%PROJECT_NAME%");

        app_context.main_loop(
                [&](GLFWwindow* window, float delta_time) -> bool
                {
                    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    return true;
                });
        return 0;
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
    }
    return 1;
}
