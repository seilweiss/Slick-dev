#include "Render/Viewport.h"

namespace Slick {

    namespace Render {

        Viewport::Viewport(QWidget* parent) :
            QOpenGLWidget(parent),
            QOpenGLFunctions_2_0(),
            m_camera(new Camera)
        {
            QSurfaceFormat format;
            format.setVersion(2, 0);
            format.setProfile(QSurfaceFormat::CompatibilityProfile);

            setFormat(format);
        }

        void Viewport::initializeGL()
        {
            initializeOpenGLFunctions();

            emit initialized();
        }

        void Viewport::paintGL()
        {
        }

        void Viewport::resizeGL(int w, int h)
        {

        }

    }

}
