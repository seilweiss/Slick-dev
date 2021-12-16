#include "Core/Viewport.h"

#include "Core/Camera.h"
#include "CameraControllers/FirstPersonCameraController.h"

#include <QDateTime>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFocusEvent>

namespace Slick {

    Viewport::Viewport(RenderContext* context, QWindow* parent) :
        QOpenGLWindow(NoPartialUpdate, parent),
        m_context(context),
        m_mouseCaptured(false),
        m_mouseCaptureStartedMoving(false),
        m_captureSaveMousePos()
    {
        setCameraController(new FirstPersonCameraController(context));
    }

    void Viewport::setCameraController(CameraController* camController)
    {
        m_camController = camController;
    }

    void Viewport::captureMouse()
    {
        if (m_mouseCaptured)
        {
            return;
        }

        m_mouseCaptured = true;
        m_mouseCaptureStartedMoving = false;

        setCursor(Qt::BlankCursor);
        m_captureSaveMousePos = cursor().pos();
        QCursor::setPos(mapToGlobal(center()));
    }

    void Viewport::freeMouse()
    {
        if (!m_mouseCaptured)
        {
            return;
        }

        m_mouseCaptured = false;
        m_mouseCaptureStartedMoving = false;

        unsetCursor();
        QCursor::setPos(m_captureSaveMousePos);
    }

    void Viewport::initializeGL()
    {
        m_context->initialize();
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
        if (m_mouseCaptured)
        {
            if ((event->pos() - center()).manhattanLength() < 20)
            {
                m_mouseCaptureStartedMoving = true;
            }

            QCursor::setPos(mapToGlobal(center()));
        }

        if (m_camController)
        {
            QPoint delta(0.0f, 0.0f);

            if (!m_mouseCaptured || m_mouseCaptureStartedMoving)
            {
                delta = event->pos() - center();
            }

            m_camController->mouseMoveEvent(event, delta);
        }

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
