#include "Render/Viewport.h"

#include "Render/Camera.h"

#include <QDateTime>

namespace Slick {

    namespace Render {

        Viewport::Viewport(QWindow* parent) :
            QOpenGLWindow(NoPartialUpdate, parent),
            QOpenGLFunctions_2_0(),
            m_prevUpdateTime(QDateTime::currentMSecsSinceEpoch())
        {
            m_context = {};
            m_context.viewport = this;
            m_context.camera = new Render::Camera(this);
        }

        void Viewport::initializeGL()
        {
            initializeOpenGLFunctions();
        }

        void Viewport::paintGL()
        {
            /*
            glClearColor (0.0, 0.0, 0.0, 0.0);
           glClear (GL_COLOR_BUFFER_BIT);
           glColor3f (1.0, 1.0, 1.0);
           glLoadIdentity();
           glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
           glBegin(GL_POLYGON);
              glVertex3f (0.25, 0.25, 0.0);
              glVertex3f (0.75, 0.25, 0.0);
              glVertex3f (0.75, 0.75, 0.0);
              glVertex3f (0.25, 0.75, 0.0);
           glEnd();
    */

            render(m_context);
            requestUpdate();
        }

        void Viewport::resizeGL(int w, int h)
        {
            /*
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);

            glm::mat4 projection = glm::perspective(60.0f, (float)w / h, 0.1f, 1000.0f);

            glLoadMatrixf(glm::value_ptr(projection));

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            */
        }

        bool Viewport::event(QEvent* e)
        {
            if (e->type() == QEvent::UpdateRequest)
            {
                qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
                float dt = (currentTime / 1000.0f) - (m_prevUpdateTime / 1000.0f);

                update(dt);

                m_prevUpdateTime = currentTime;
            }

            return QOpenGLWindow::event(e);
        }

    }

}
