#include "render/controllers/firstpersoncameracontroller.h"

#include "render/context.h"
#include "render/viewport.h"
#include "util/mathutils.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QFocusEvent>

namespace Slick {

    namespace Render {

        FirstPersonCameraController::FirstPersonCameraController(Context* context, QObject* parent) :
            CameraController(context, parent),
            m_moveSpeed(50.0f),
            m_rotateSpeed(glm::radians(20.0f)),
            m_pos(0.0f),
            m_rot(0.0f),
            m_scale(1.0f),
            m_oldVel(0.0f),
            m_oldDYaw(0.0f),
            m_oldDPitch(0.0f),
            m_freeLook(false),
            m_moveForward(false),
            m_moveBackward(false),
            m_moveLeft(false),
            m_moveRight(false),
            m_moveUp(false),
            m_moveDown(false),
            m_sprint(false),
            m_sneak(false),
            m_lookDelta()
        {
        }

        void FirstPersonCameraController::update()
        {
            float dt = context()->deltaTime();
            float dyaw = 0.0f;
            float dpitch = 0.0f;
            glm::vec3 vel(0.0f);

            if (m_freeLook)
            {
                dyaw = -(float)m_lookDelta.x();
                dpitch = -(float)m_lookDelta.y();

                dyaw *= m_rotateSpeed * dt;
                dpitch *= m_rotateSpeed * dt;

                vel.x = (m_moveRight ? 1.0f : 0.0f) - (m_moveLeft ? 1.0f : 0.0f);
                vel.y = (m_moveUp ? 1.0f : 0.0f) - (m_moveDown ? 1.0f : 0.0f);
                vel.z = (m_moveBackward ? 1.0f : 0.0f) - (m_moveForward ? 1.0f : 0.0f);

                if (glm::length2(vel) > 0.0f)
                {
                    vel = glm::normalize(vel);
                }

                vel *= m_moveSpeed * dt;

                if (m_sprint != m_sneak)
                {
                    if (m_sprint)
                    {
                        vel *= 5.0f;
                    }
                    else
                    {
                        vel /= 5.0f;
                    }
                }
            }

            if (dyaw == 0.0f) dyaw = m_oldDYaw * 0.5f;
            if (dpitch == 0.0f) dpitch = m_oldDPitch * 0.5f;
            if (vel.x == 0.0f) vel.x = m_oldVel.x * 0.75f;
            if (vel.y == 0.0f) vel.y = m_oldVel.y * 0.75f;
            if (vel.z == 0.0f) vel.z = m_oldVel.z * 0.75f;

            m_rot[0] += dpitch;
            m_rot[1] += dyaw;

            glm::mat4 mat(1.0f);
            mat = glm::translate(mat, m_pos);
            mat = glm::rotate(mat, m_rot[2], glm::vec3(0, 0, 1));
            mat = glm::rotate(mat, m_rot[1], glm::vec3(0, 1, 0));
            mat = glm::rotate(mat, m_rot[0], glm::vec3(1, 0, 0));
            mat = glm::translate(mat, vel);

            m_pos = mat[3];

            mat = glm::scale(mat, m_scale);

            context()->camera()->setViewMatrix(mat);

            m_oldVel = vel;
            m_oldDYaw = dyaw;
            m_oldDPitch = dpitch;
            m_lookDelta = QPoint();
        }

        void FirstPersonCameraController::setViewMatrix(const glm::mat4& mat)
        {
            CameraController::setViewMatrix(mat);

            m_pos = mat[3];
            m_oldVel = glm::vec3(0.0f);

            Util::decomposeMatrix(mat, m_pos, m_rot, m_scale);

            m_oldDYaw = 0.0f;
            m_oldDPitch = 0.0f;
        }

        void FirstPersonCameraController::mousePressEvent(QMouseEvent* event)
        {
            if (event->button() == Qt::RightButton)
            {
                m_freeLook = true;
                context()->viewport()->captureMouse();
            }
        }

        void FirstPersonCameraController::mouseReleaseEvent(QMouseEvent* event)
        {
            if (event->button() == Qt::RightButton)
            {
                m_freeLook = false;
                context()->viewport()->freeMouse();
            }
        }

        void FirstPersonCameraController::mouseMoveEvent(QMouseEvent* event, const QPoint& delta)
        {
            if (m_freeLook)
            {
                m_lookDelta = delta;
            }
        }

        void FirstPersonCameraController::wheelEvent(QWheelEvent* event)
        {
            if (m_freeLook)
            {
                m_moveSpeed += event->angleDelta().y() / 15.0f;
                m_rotateSpeed += event->angleDelta().x() / 15.0f;

                m_moveSpeed = qBound(1.0f, m_moveSpeed, 500.0f);
                m_rotateSpeed = qBound(glm::radians(1.0f), m_rotateSpeed, glm::radians(100.0f));
            }
        }

        void FirstPersonCameraController::keyPressEvent(QKeyEvent* event)
        {
            bool handled = true;

            switch (event->key())
            {
            case Qt::Key_W:
            case Qt::Key_Up:
                m_moveForward = true;
                break;
            case Qt::Key_A:
            case Qt::Key_Left:
                m_moveLeft = true;
                break;
            case Qt::Key_S:
            case Qt::Key_Down:
                m_moveBackward = true;
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                m_moveRight = true;
                break;
            case Qt::Key_E:
            case Qt::Key_Space:
                m_moveUp = true;
                break;
            case Qt::Key_Q:
            case Qt::Key_Alt:
                m_moveDown = true;
                break;
            case Qt::Key_Shift:
                m_sprint = true;
                break;
            case Qt::Key_Control:
                m_sneak = true;
                break;
            default:
                handled = false;
                break;
            }

            if (handled)
            {
                event->accept();
            }
        }

        void FirstPersonCameraController::keyReleaseEvent(QKeyEvent* event)
        {
            bool handled = true;

            switch (event->key())
            {
            case Qt::Key_W:
            case Qt::Key_Up:
                m_moveForward = false;
                break;
            case Qt::Key_A:
            case Qt::Key_Left:
                m_moveLeft = false;
                break;
            case Qt::Key_S:
            case Qt::Key_Down:
                m_moveBackward = false;
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                m_moveRight = false;
                break;
            case Qt::Key_E:
            case Qt::Key_Space:
                m_moveUp = false;
                break;
            case Qt::Key_Q:
            case Qt::Key_Alt:
                m_moveDown = false;
                break;
            case Qt::Key_Shift:
                m_sprint = false;
                break;
            case Qt::Key_Control:
                m_sneak = false;
                break;
            default:
                handled = false;
                break;
            }

            if (handled)
            {
                event->accept();
            }
        }

        void FirstPersonCameraController::focusInEvent(QFocusEvent* event)
        {
        }

        void FirstPersonCameraController::focusOutEvent(QFocusEvent* event)
        {
            m_freeLook = false;
            context()->viewport()->freeMouse();
        }

    }

}
