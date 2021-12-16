#include "Core/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    Camera::Camera(RenderContext* context) :
        QObject(context),
        m_context(context),
        m_proj(),
        m_projMatrix(),
        m_viewMatrix(1.0f),
        m_begun(false)
    {
        Q_ASSERT(context);

        m_proj.type = Projection::Perspective;
        m_proj.aspect = 1.0f;
        m_proj.nearClip = 0.05f;
        m_proj.farClip = 400.0f;
        m_proj.fov = glm::radians(60.0f);

        calcProjMatrix();
    }

    void Camera::begin()
    {
        Q_ASSERT(m_context->isInitialized());
        Q_ASSERT(!m_begun);

#ifdef QT_DEBUG
        GLint stackDepth;
        m_context->glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &stackDepth);

        Q_ASSERT(stackDepth == 1);
#endif

        glm::mat4 inverseViewMatrix = glm::inverse(m_viewMatrix);

        m_context->glMatrixMode(GL_PROJECTION);
        m_context->glLoadMatrixf(glm::value_ptr(m_projMatrix));

        m_context->glMatrixMode(GL_MODELVIEW);
        m_context->glLoadMatrixf(glm::value_ptr(inverseViewMatrix));

        m_begun = true;
    }

    void Camera::end()
    {
        Q_ASSERT(m_begun);

#ifdef QT_DEBUG
        GLint stackDepth;
        m_context->glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &stackDepth);

        Q_ASSERT(stackDepth == 1);
#endif

        m_begun = false;
    }

    void Camera::setProjection(const Projection& proj)
    {
        m_proj = proj;

        calcProjMatrix();
    }

    void Camera::setViewMatrix(const glm::mat4& mat)
    {
        m_viewMatrix = mat;
    }

    void Camera::calcProjMatrix()
    {
        if (m_proj.type == Projection::Perspective)
        {
            m_projMatrix = glm::perspective(m_proj.fov, m_proj.aspect, m_proj.nearClip, m_proj.farClip);
        }
        else
        {
            m_projMatrix = glm::ortho(m_proj.left, m_proj.right, m_proj.bottom, m_proj.top);
        }
    }

}
