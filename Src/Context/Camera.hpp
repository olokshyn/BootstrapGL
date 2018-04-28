//
// Created by oleg on 24.02.18.
//

#ifndef TRANSFORMATIONS_CAMERA_HPP
#define TRANSFORMATIONS_CAMERA_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

namespace BootstrapGL
{

class Camera
{
public:
    enum Direction
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

public:
    explicit Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 1.0f),
                    const glm::vec3& front = glm::vec3(0.0f, 0.0f, -1.0f));

    const glm::mat4& view_matrix() const;

    const glm::vec3& position() const;
    const glm::vec3& front() const;

    float field_of_view() const;

    void move_camera(Direction direction, float delta_time);

    void process_keyboard_move(int key, float delta_time);

    void process_mouse_move(float xoffset, float yoffset);

    void process_mouse_scroll(float offset);

private:
    void update();

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
    mutable glm::mat4 m_view_matrix;
    mutable bool m_cache_valid;
    float m_pitch;
    float m_yaw;
    float m_speed;
    float m_sensitivity;
    float m_zoom;
};

}

#endif //TRANSFORMATIONS_CAMERA_HPP
