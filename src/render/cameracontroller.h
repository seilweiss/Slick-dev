#pragma once

#include "render/camera.h"

Q_MOC_INCLUDE("render/context.h")

class QMouseEvent;
class QKeyEvent;
class QFocusEvent;
class QWheelEvent;

namespace Slick {

    namespace Render {

        class CameraController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(Context* context READ context)

        public:
            CameraController(Context* context, QObject* parent = nullptr);

            Context* context() const { return m_context; }

            virtual void update() = 0;
            virtual void mousePressEvent(QMouseEvent* event) { Q_UNUSED(event); }
            virtual void mouseReleaseEvent(QMouseEvent* event) { Q_UNUSED(event); }
            virtual void mouseMoveEvent(QMouseEvent* event, const QPoint& delta) { Q_UNUSED(event); Q_UNUSED(delta); }
            virtual void wheelEvent(QWheelEvent* event) { Q_UNUSED(event); }
            virtual void keyPressEvent(QKeyEvent* event) { Q_UNUSED(event); }
            virtual void keyReleaseEvent(QKeyEvent* event) { Q_UNUSED(event); }
            virtual void focusInEvent(QFocusEvent* event) { Q_UNUSED(event); }
            virtual void focusOutEvent(QFocusEvent* event) { Q_UNUSED(event); }

        private:
            Context* m_context;
        };

    }

}
