#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}

Camera::Camera(glm::vec3 start_position, glm::vec3 world_up, GLfloat start_yaw, GLfloat start_pitch, GLfloat move_speed, GLfloat turn_speed)
{
    m_position = start_position;
    m_world_up = world_up;
    m_yaw = start_yaw;
    m_pitch = start_pitch;
    m_move_speed = move_speed;
    m_turn_speed = turn_speed;
    m_front = glm::vec3(0.0, 0.0, -1.0f);

    update();
}

void Camera::handleKeyPress(const std::vector<bool>& keys, GLfloat delta_time)
{
    auto velocity = m_move_speed * delta_time;
    if(keys[GLFW_KEY_W]) {
        m_position += m_front * velocity;
    }
    if(keys[GLFW_KEY_S]) {
        m_position -= m_front * velocity;
    }
    if(keys[GLFW_KEY_A]) {
        m_position -= m_right * velocity;
    }
    if(keys[GLFW_KEY_D]) {
        m_position += m_right * velocity;
    }
}

void Camera::handleMouseMove(double x_change, double y_change)
{
    x_change *= m_turn_speed;
    y_change *= m_turn_speed;

    m_yaw += x_change;
    m_pitch += y_change;

    if (m_pitch > 89.0f) {
        m_pitch = 89.0f;
    }

    if (m_pitch < -89.0f) {
        m_pitch = -89.0f;
    }

    update();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(m_position, m_front, m_up);
}

void Camera::update()
{
    m_front.x = glm::cos(glm::radians(m_pitch))*glm::cos(glm::radians((m_yaw)));
    m_front.y = glm::sin(glm::radians(m_pitch));
    m_front.z = glm::cos(glm::radians(m_pitch))*glm::sin(glm::radians(m_yaw));
    m_front = glm::normalize(m_front);
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}