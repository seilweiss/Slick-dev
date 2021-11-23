#include "Render/Camera.h"

#include "Render/Viewport.h"

namespace Slick {

    namespace Render {

        Camera::Camera(Viewport* viewport) :
            QObject(viewport),
            m_viewport(viewport)
        {
        }

        void Camera::clear(int buffers)
        {
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

            m_viewport->glClear(glBuffers);
        }

        QColor Camera::clearColor() const
        {
            GLint color[4];

            m_viewport->glGetIntegerv(GL_COLOR_CLEAR_VALUE, color);

            return QColor(color[0], color[1], color[2], color[3]);
        }

        void Camera::setClearColor(const QColor& color)
        {
            m_viewport->glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        }

        bool Camera::fogEnabled() const
        {
            GLboolean enabled;

            m_viewport->glGetBooleanv(GL_FOG, &enabled);

            return enabled;
        }

        void Camera::setFogEnabled(bool enabled)
        {
            if (enabled)
            {
                m_viewport->glEnable(GL_FOG);
            }
            else
            {
                m_viewport->glDisable(GL_FOG);
            }
        }

        FogType Camera::fogType() const
        {
            GLint mode;

            m_viewport->glGetIntegerv(GL_FOG_MODE, &mode);

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
            GLint mode;

            switch (type)
            {
            case FogLinear: mode = GL_LINEAR; break;
            case FogExp: mode = GL_EXP; break;
            case FogExp2: mode = GL_EXP2; break;
            default: mode = GL_LINEAR; break;
            }

            m_viewport->glFogi(GL_FOG_MODE, mode);
        }

        float Camera::fogDensity() const
        {
            GLfloat density;

            m_viewport->glGetFloatv(GL_FOG_DENSITY, &density);

            return density;
        }

        void Camera::setFogDensity(float density)
        {
            m_viewport->glFogf(GL_FOG_DENSITY, density);
        }

        float Camera::fogStart() const
        {
            GLfloat start;

            m_viewport->glGetFloatv(GL_FOG_START, &start);

            return start;
        }

        void Camera::setFogStart(float start)
        {
            m_viewport->glFogf(GL_FOG_START, start);
        }

        float Camera::fogEnd() const
        {
            GLfloat end;

            m_viewport->glGetFloatv(GL_FOG_END, &end);

            return end;
        }

        void Camera::setFogEnd(float end)
        {
            m_viewport->glFogf(GL_FOG_END, end);
        }

        QColor Camera::fogColor() const
        {
            GLint color[4];

            m_viewport->glGetIntegerv(GL_FOG_COLOR, color);

            return QColor(color[0], color[1], color[2], color[3]);
        }

        void Camera::setFogColor(const QColor& color)
        {
            GLfloat c[4] = { color.redF(), color.greenF(), color.blueF(), color.alphaF() };

            m_viewport->glFogfv(GL_FOG_COLOR, c);
        }

    }

}
