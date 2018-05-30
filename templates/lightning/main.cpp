#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>

#include "BootstrapGL/Context/AppContext.hpp"
#include "BootstrapGL/Shader/ShaderProgram.hpp"
#include "BootstrapGL/Shader/ActiveShaderProgramGuard.hpp"
#include "BootstrapGL/VAO/VertexArray.hpp"
#include "BootstrapGL/Light/DirectionalLight.hpp"
#include "BootstrapGL/Light/SpotLight.hpp"
#include "BootstrapGL/Light/PointLight.hpp"
#include "BootstrapGL/Texture/Material.hpp"

using namespace BootstrapGL;

static const float g_vertices[] = {
        // positions         // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

static const glm::vec3 g_cube_positions[] = {
        glm::vec3( 0.0f,  0.0f,  -0.5f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

size_t g_cube_positions_count = sizeof(g_cube_positions) / sizeof(g_cube_positions[0]);

int main()
{
    try
    {
        const size_t screen_width = 1360;
        const size_t screen_height = 768;

        auto& app_context = AppContext::CreateContext(screen_width,
                                                      screen_height,
                                                      "%PROJECT_NAME%");

        ShaderProgram shader_program("shaders/vertex.glsl",
                                     "shaders/fragment.glsl");
        ShaderProgram light_shader_program("shaders/vertex_light.glsl",
                                           "shaders/fragment_light.glsl");

        VertexArray light_cube_vao(
                [](unsigned int vbo)
                {
                    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices),
                                 g_vertices, GL_STATIC_DRAW);
                },
                [](unsigned int vao)
                {
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                          8 * sizeof(float),
                                          reinterpret_cast<void*>(0));
                    glEnableVertexAttribArray(0);
                });

        VertexArray cube_vao(
                [](unsigned int vbo)
                {
                    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices),
                                 g_vertices, GL_STATIC_DRAW);
                },
                [](unsigned int vao)
                {
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                          8 * sizeof(float),
                                          reinterpret_cast<void*>(0));
                    glEnableVertexAttribArray(0);

                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                                          8 * sizeof(float),
                                          reinterpret_cast<void*>(3 * sizeof(float)));
                    glEnableVertexAttribArray(1);

                    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                                          8 * sizeof(float),
                                          reinterpret_cast<void*>(6 * sizeof(float)));
                    glEnableVertexAttribArray(2);
                });

        DirectionalLight directional_light(glm::vec3(1.5f, 0.0f, 3.0f),
                                           glm::vec3(0.05f), glm::vec3(0.3f), glm::vec3(0.5f));
        PointLight point_light(glm::vec3(0.5f,  0.5f,  0.3f),
                               glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(0.5f));
        SpotLight spot_light(PointLight(app_context.camera().position(),
                                        glm::vec3(0.0f), glm::vec3(0.8f), glm::vec3(0.8f)),
                             app_context.camera().front());
        spot_light.disable();

        Material cube_material(Texture(TextureInfo("textures/container.png"), 0),
                               Texture(TextureInfo("textures/container_specular.png"), 1));

        app_context.set_key_handler(
                [&](GLFWwindow* window,
                    int key, int scancode,
                    int action, int mods,
                    float delta_time)
                {
                    if (action == GLFW_PRESS && key == GLFW_KEY_F)
                    {
                        spot_light.toggle();
                    }
                });

        app_context.main_loop(
                [&](GLFWwindow* window, float delta_time) -> bool
                {
                    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    const glm::mat4& view_matrix = app_context.camera().view_matrix();

                    glm::mat4 projection_matrix = glm::perspective(
                            glm::radians(app_context.camera().field_of_view()),
                            static_cast<float>(screen_width) / screen_height,
                            0.1f, 100.0f);

                    glm::mat4 model_matrix(1.0f);

                    model_matrix = glm::translate(model_matrix, point_light.position());
                    model_matrix = glm::scale(model_matrix, glm::vec3(0.2f));

                    ActiveShaderProgramGuard active_shader_program_guard(&light_shader_program);
                    light_shader_program.set_uniform("model_matrix", model_matrix);
                    light_shader_program.set_uniform("view_matrix", view_matrix);
                    light_shader_program.set_uniform("projection_matrix", projection_matrix);
                    light_cube_vao.use();
                    glDrawArrays(GL_TRIANGLES, 0, 36);

                    active_shader_program_guard = shader_program;
                    shader_program.set_uniform("view_matrix", view_matrix);
                    shader_program.set_uniform("projection_matrix", projection_matrix);
                    shader_program.set_uniform("viewer_position",
                                               app_context.camera().position());
                    directional_light.set_light(shader_program, "directional_light");
                    point_light.set_light(shader_program, "point_light");
                    spot_light.position() = app_context.camera().position();
                    spot_light.direction() = app_context.camera().front();
                    spot_light.set_light(shader_program, "spot_light");
                    cube_material.set_material(shader_program, "material");

                    cube_vao.use();
                    for (size_t i = 0; i != g_cube_positions_count; ++i)
                    {
                        model_matrix = glm::mat4(1.0f);
                        model_matrix = glm::translate(model_matrix, g_cube_positions[i]);
                        shader_program.set_uniform("model_matrix", model_matrix);

                        glDrawArrays(GL_TRIANGLES, 0, 36);
                    }

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
