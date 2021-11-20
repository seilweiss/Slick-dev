#include "Render/Camera.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLVersionFunctionsFactory>

#define GET_OPENGL_FUNCTIONS() QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_2_0>(QOpenGLContext::currentContext());

namespace Slick {

    namespace Render {

        Camera::Camera(QObject* parent) :
            QObject(parent)
        {
        }

        void Camera::clear(int buffers)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLbitfield glBuffers = 0;

            if (buffers & ColorBuffer)
            {
                glBuffers |= GL_COLOR_BUFFER_BIT;
            }

            if (buffers & DepthBuffer)
            {
                glBuffers |= GL_DEPTH_BUFFER_BIT;
            }

            if (buffers & StencilBuffer)
            {
                glBuffers |= GL_STENCIL_BUFFER_BIT;
            }

            glFuncs->glClear(glBuffers);
        }

        QColor Camera::clearColor() const
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLint color[4];

            glFuncs->glGetIntegerv(GL_COLOR_CLEAR_VALUE, color);

            return QColor(color[0], color[1], color[2], color[3]);
        }

        void Camera::setClearColor(const QColor& color)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();

            glFuncs->glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        }

        bool Camera::fogEnabled() const
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLboolean enabled;

            glFuncs->glGetBooleanv(GL_FOG, &enabled);

            return enabled;
        }

        void Camera::setFogEnabled(bool enabled)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();

            if (enabled)
            {
                glFuncs->glEnable(GL_FOG);
            }
            else
            {
                glFuncs->glDisable(GL_FOG);
            }
        }

        FogType Camera::fogType() const
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLint mode;

            glFuncs->glGetIntegerv(GL_FOG_MODE, &mode);

            switch (mode)
            {
            case GL_LINEAR: return FogLinear;
            case GL_EXP: return FogExp;
            case GL_EXP2: return FogExp2;
            default: return FogLinear;
            }
        }

        void Camera::setFogType(FogType type)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLint mode;

            switch (type)
            {
            case FogLinear: mode = GL_LINEAR; break;
            case FogExp: mode = GL_EXP; break;
            case FogExp2: mode = GL_EXP2; break;
            default: mode = GL_LINEAR; break;
            }

            glFuncs->glFogi(GL_FOG_MODE, mode);
        }

        float Camera::fogDensity() const
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLfloat density;

            glFuncs->glGetFloatv(GL_FOG_DENSITY, &density);

            return density;
        }

        void Camera::setFogDensity(float density)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();

            glFuncs->glFogf(GL_FOG_DENSITY, density);
        }

        float Camera::fogStart() const
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLfloat start;

            glFuncs->glGetFloatv(GL_FOG_START, &start);

            return start;
        }

        void Camera::setFogStart(float start)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();

            glFuncs->glFogf(GL_FOG_START, start);
        }

        float Camera::fogEnd() const
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLfloat end;

            glFuncs->glGetFloatv(GL_FOG_END, &end);

            return end;
        }

        void Camera::setFogEnd(float end)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();

            glFuncs->glFogf(GL_FOG_END, end);
        }

        QColor Camera::fogColor() const
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLint color[4];

            glFuncs->glGetIntegerv(GL_FOG_COLOR, color);

            return QColor(color[0], color[1], color[2], color[3]);
        }

        void Camera::setFogColor(const QColor& color)
        {
            auto glFuncs = GET_OPENGL_FUNCTIONS();
            GLfloat c[4] = { color.redF(), color.greenF(), color.blueF(), color.alphaF() };

            glFuncs->glFogfv(GL_FOG_COLOR, c);
        }

    }

}
