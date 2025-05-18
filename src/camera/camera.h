#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Camera
{
public:

    Camera();

    Camera(glm::vec3 start_position, glm::vec3 world_up, GLfloat start_yaw, GLfloat start_pitch, GLfloat move_speed, GLfloat turn_speed);

    void handleKeyPress(const std::vector<bool>& keys, GLfloat delta_time);

    void handleMouseMove(double x_change, double y_change);

    glm::mat4 getViewMatrix() const;

private:

    void update();

    glm::vec3 m_world_up;;
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    GLfloat m_yaw;
    GLfloat m_pitch;
    GLfloat m_move_speed;
    GLfloat m_turn_speed;
};