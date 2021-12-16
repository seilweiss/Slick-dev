#pragma once

#include "Core/CameraController.h"

#include <QPoint>

namespace Slick {

    class FirstPersonCameraController : public CameraController
    {
        Q_OBJECT

    public:
        FirstPersonCameraController(RenderContext* context);

        float moveSpeed() const { return m_moveSpeed; }
        void setMoveSpeed(float speed) { m_moveSpeed = speed; }

        float rotateSpeed() const { return m_rotateSpeed; }
        void setRotateSpeed(float speed) { m_rotateSpeed = speed; }

    protected:
        virtual void update() override;
        virtual void mousePressEvent(QMouseEvent* event) override;
        virtual void mouseReleaseEvent(QMouseEvent* event) override;
        virtual void mouseMoveEvent(QMouseEvent* event, const QPoint& delta) override;
        virtual void wheelEvent(QWheelEvent* event) override;
        virtual void keyPressEvent(QKeyEvent* event) override;
        virtual void keyReleaseEvent(QKeyEvent* event) override;
        virtual void focusInEvent(QFocusEvent* event) override;
        virtual void focusOutEvent(QFocusEvent* event) override;

    private:
        float m_moveSpeed;
        float m_rotateSpeed;
        glm::vec3 m_pos;
        float m_yaw;
        float m_pitch;
        glm::vec3 m_oldVel;
        float m_oldDYaw;
        float m_oldDPitch;
        bool m_freeLook;
        bool m_moveForward;
        bool m_moveBackward;
        bool m_moveLeft;
        bool m_moveRight;
        bool m_moveUp;
        bool m_moveDown;
        bool m_sprint;
        bool m_sneak;
        QPoint m_lookDelta;
    };

}
