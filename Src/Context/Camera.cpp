//
// Created by oleg on 24.02.18.
//

#include "Camera.hpp"

#include <algorithm>


namespace
{

const float g_pitch = 0.0f;
const float g_yaw = -90.0f;
const float g_speed = 25.0f;
const float g_sensitivity = 0.1f;
const float g_zoom = 45.0f;

}

using namespace BootstrapGL;

Camera::Camera(const glm::vec3& position,
               const glm::vec3& front)
        : m_position(position),
          m_front(front),
          m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
          m_right(glm::vec3(1.0f, 0.0f, 0.0f)),
          m_world_up(m_up),
          m_cache_valid(false),
          m_pitch(g_pitch),
          m_yaw(g_yaw),
          m_speed(g_speed),
          m_sensitivity(g_sensitivity),
          m_zoom(g_zoom)
{
    update();
}

const glm::mat4& Camera::view_matrix() const
{
    if (!m_cache_valid)
    {
        m_view_matrix = glm::lookAt(m_position,
                                    m_position + m_front,
                                    m_up);
        m_cache_valid = true;
    }
    return m_view_matrix;
}

const glm::vec3& Camera::position() const
{
    return m_position;
}

const glm::vec3& Camera::front() const
{
    return m_front;
}

float Camera::field_of_view() const
{
    return m_zoom;
}

void Camera::move_camera(Direction direction, float delta_time)
{
    float velocity = m_speed * delta_time;
    switch (direction)
    {
    case FORWARD:
        m_position += m_front * velocity;
        break;
    case BACKWARD:
        m_position -= m_front * velocity;
        break;
    case RIGHT:
        m_position += m_right * velocity;
        break;
    case LEFT:
        m_position -= m_right * velocity;
        break;
    }

    update();
}

void Camera::process_keyboard_move(int key, float delta_time)
{
    switch (key)
    {
    case GLFW_KEY_W:
        move_camera(FORWARD, delta_time);
        break;
    case GLFW_KEY_S:
        move_camera(BACKWARD, delta_time);
        break;
    case GLFW_KEY_D:
        move_camera(RIGHT, delta_time);
        break;
    case GLFW_KEY_A:
        move_camera(LEFT, delta_time);
        break;
    default:
        break;
    }
}

void Camera::process_mouse_move(float xoffset, float yoffset)
{
    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    m_pitch = std::min(m_pitch, 89.0f);
    m_pitch = std::max(m_pitch, -89.0f);

    update();
}

void Camera::process_mouse_scroll(float offset)
{
    if (m_zoom >= 1.0f && m_zoom <= 45.0f)
    {
        m_zoom -= offset;
    }
    if (m_zoom <= 1.0f)
    {
        m_zoom = 1.0f;
    }
    if (m_zoom >= 45.0f)
    {
        m_zoom = 45.0f;
    }
}

void Camera::update()
{
    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(m_yaw))
                                 * cos(glm::radians(m_pitch)));
    front.y = static_cast<float>(sin(glm::radians(m_pitch)));
    front.z = static_cast<float>(sin(glm::radians(m_yaw))
                                 * cos(glm::radians(m_pitch)));
    m_front = glm::normalize(front);
    m_right = glm::normalize(
            glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));

    m_cache_valid = false;
}
