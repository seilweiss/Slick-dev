#include "render/viewport.h"

#include "render/camera.h"
#include "render/controllers/firstpersoncameracontroller.h"

#include <QDateTime>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFocusEvent>

namespace Slick {

    namespace Render {

        Viewport::Viewport(QWindow* parent) :
            QOpenGLWindow(NoPartialUpdate, parent),
            m_context(nullptr),
            m_camController(nullptr),
            m_mouseCaptured(false),
            m_captureSaveMousePos(),
            m_lastMousePos()
        {
        }

        void Viewport::setCameraController(CameraController* camController)
        {
            m_camController = camController;
        }

        void Viewport::captureMouse()
        {
            if (!m_mouseCaptured)
            {
                m_mouseCaptured = true;
                m_captureSaveMousePos = QCursor::pos();
                //setCursor(Qt::ClosedHandCursor);
                setCursor(Qt::BlankCursor);
            }
        }

        void Viewport::freeMouse()
        {
            if (m_mouseCaptured)
            {
                m_mouseCaptured = false;
                QCursor::setPos(m_captureSaveMousePos);
                unsetCursor();
            }
        }

        void Viewport::initializeGL()
        {
            Q_ASSERT(m_context);

            m_context->initialize();

            if (!m_camController)
            {
                setCameraController(new FirstPersonCameraController(m_context, this));
            }
        }

        void Viewport::paintGL()
        {
            render();
            requestUpdate();
        }

        void Viewport::resizeGL(int w, int h)
        {
            m_context->glViewport(0, 0, w, h);

            Projection proj = m_context->camera()->projection();
            proj.aspect = (float)w / h;

            m_context->camera()->setProjection(proj);
        }

        void Viewport::update()
        {
            if (m_camController)
            {
                m_camController->update();
            }
        }

        void Viewport::render()
        {
        }

        bool Viewport::event(QEvent* event)
        {
            if (event->type() == QEvent::UpdateRequest)
            {
                m_context->beginFrame();

                update();
            }

            return QOpenGLWindow::event(event);
        }

        void Viewport::mousePressEvent(QMouseEvent* event)
        {
            if (m_camController)
            {
                m_camController->mousePressEvent(event);
            }

            if (!event->isAccepted())
            {
                QOpenGLWindow::mousePressEvent(event);
            }
        }

        void Viewport::mouseReleaseEvent(QMouseEvent* event)
        {
            if (m_camController)
            {
                m_camController->mouseReleaseEvent(event);
            }

            if (!event->isAccepted())
            {
                QOpenGLWindow::mouseReleaseEvent(event);
            }
        }

        void Viewport::mouseMoveEvent(QMouseEvent* event)
        {
            QPoint delta = event->pos() - m_lastMousePos;

            if (abs(delta.x()) > width() * 0.75f || abs(delta.y()) > height() * 0.75f)
            {
                event->accept();
                return;
            }

            if (m_camController)
            {
                m_camController->mouseMoveEvent(event, delta);
            }

            bool relocate = false;
            QPoint newPos = event->pos();

            if (newPos.x() >= width())
            {
                relocate = true;
                newPos.setX(newPos.x() - width());
            }
            else if (newPos.x() < 0)
            {
                relocate = true;
                newPos.setX(newPos.x() + width());
            }

            if (newPos.y() >= height())
            {
                relocate = true;
                newPos.setY(newPos.y() - height());
            }
            else if (newPos.y() < 0)
            {
                relocate = true;
                newPos.setY(newPos.y() + height());
            }

            if (relocate)
            {
                QCursor::setPos(mapToGlobal(newPos));
            }

            m_lastMousePos = newPos;

            if (!event->isAccepted())
            {
                QOpenGLWindow::mouseMoveEvent(event);
            }
        }

        void Viewport::wheelEvent(QWheelEvent* event)
        {
            if (m_camController)
            {
                m_camController->wheelEvent(event);
            }

            if (!event->isAccepted())
            {
                QOpenGLWindow::wheelEvent(event);
            }
        }

        void Viewport::keyPressEvent(QKeyEvent* event)
        {
            if (m_camController)
            {
                m_camController->keyPressEvent(event);
            }

            if (!event->isAccepted())
            {
                QOpenGLWindow::keyPressEvent(event);
            }
        }

        void Viewport::keyReleaseEvent(QKeyEvent* event)
        {
            if (m_camController)
            {
                m_camController->keyReleaseEvent(event);
            }

            if (!event->isAccepted())
            {
                QOpenGLWindow::keyReleaseEvent(event);
            }
        }

        void Viewport::focusInEvent(QFocusEvent* event)
        {
            if (m_camController)
            {
                m_camController->focusInEvent(event);
            }

            if (!event->isAccepted())
            {
                QOpenGLWindow::focusInEvent(event);
            }
        }

        void Viewport::focusOutEvent(QFocusEvent* event)
        {
            if (m_camController)
            {
                m_camController->focusOutEvent(event);
            }

            if (!event->isAccepted())
            {
                QOpenGLWindow::focusOutEvent(event);
            }
        }

    }

}
