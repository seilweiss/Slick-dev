#include "render/viewport.h"

#include "render/context.h"
#include "render/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
            m_lastMousePos(),
            m_aspectOverride(0.0f)
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
        }

        void Viewport::paintGL()
        {
            preUpdate();
            update();
            postUpdate();

            preRender();
            render();
            postRender();

            requestUpdate();
        }

        void Viewport::resizeGL(int w, int h)
        {
            // Don't call glViewport (or any GL commands) here.
            // Qt resets the viewport size right before paintGL,
            // so we need to override it there, not here.

            Q_UNUSED(w);
            Q_UNUSED(h);
        }

        void Viewport::preUpdate()
        {
            if (m_camController)
            {
                m_camController->update();
            }
        }

        void Viewport::postUpdate()
        {
        }

        void Viewport::preRender()
        {
            float w = width() * devicePixelRatio();
            float h = height() * devicePixelRatio();
            float aspect = w / h;
            float vx = 0.0f;
            float vy = 0.0f;
            float vw = w;
            float vh = h;

            if (m_aspectOverride > 0.0f)
            {
                if (aspect > m_aspectOverride)
                {
                    vw = h * m_aspectOverride;
                    vx = (w - vw) / 2.0f;
                }
                else if (aspect < m_aspectOverride)
                {
                    vh = w / m_aspectOverride;
                    vy = (h - vh) / 2.0f;
                }
            }

            m_context->glViewport(vx, vy, vw, vh);

            Projection proj = m_context->camera()->projection();
            proj.aspect = vw / vh;

            m_context->camera()->setProjection(proj);

            m_context->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            m_context->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            m_context->glPushAttrib(GL_SCISSOR_BIT);
            m_context->glEnable(GL_SCISSOR_TEST);
            m_context->glScissor(vx, vy, vw, vh);
        }

        void Viewport::postRender()
        {
            m_context->glPopAttrib();
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

            QPoint newPos = event->pos();

            if (m_mouseCaptured)
            {
                bool relocate = false;

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
