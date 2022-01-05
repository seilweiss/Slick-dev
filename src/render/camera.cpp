#include "render/camera.h"

#include "render/context.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    namespace Render {

        Camera::Camera(Context* context) :
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
            updateFrustumPlanes();
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
            updateFrustumPlanes();
        }

        void Camera::setViewMatrix(const glm::mat4& mat)
        {
            m_viewMatrix = mat;

            updateFrustumPlanes();
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

        void Camera::updateFrustumPlanes()
        {
            glm::mat4 comboMatrix = m_projMatrix * m_viewMatrix;

            // Left
            m_frustumPlanes[0][0] = comboMatrix[3][0] + comboMatrix[0][0];
            m_frustumPlanes[0][1] = comboMatrix[3][1] + comboMatrix[0][1];
            m_frustumPlanes[0][2] = comboMatrix[3][2] + comboMatrix[0][2];
            m_frustumPlanes[0][3] = comboMatrix[3][3] + comboMatrix[0][3];
            // Right
            m_frustumPlanes[1][0] = comboMatrix[3][0] - comboMatrix[0][0];
            m_frustumPlanes[1][1] = comboMatrix[3][1] - comboMatrix[0][1];
            m_frustumPlanes[1][2] = comboMatrix[3][2] - comboMatrix[0][2];
            m_frustumPlanes[1][3] = comboMatrix[3][3] - comboMatrix[0][3];
            // Bottom
            m_frustumPlanes[2][0] = comboMatrix[3][0] + comboMatrix[1][0];
            m_frustumPlanes[2][1] = comboMatrix[3][1] + comboMatrix[1][1];
            m_frustumPlanes[2][2] = comboMatrix[3][2] + comboMatrix[1][2];
            m_frustumPlanes[2][3] = comboMatrix[3][3] + comboMatrix[1][3];
            // Top
            m_frustumPlanes[3][0] = comboMatrix[3][0] - comboMatrix[1][0];
            m_frustumPlanes[3][1] = comboMatrix[3][1] - comboMatrix[1][1];
            m_frustumPlanes[3][2] = comboMatrix[3][2] - comboMatrix[1][2];
            m_frustumPlanes[3][3] = comboMatrix[3][3] - comboMatrix[1][3];
            // Near
            m_frustumPlanes[4][0] = comboMatrix[3][0] + comboMatrix[2][0];
            m_frustumPlanes[4][1] = comboMatrix[3][1] + comboMatrix[2][1];
            m_frustumPlanes[4][2] = comboMatrix[3][2] + comboMatrix[2][2];
            m_frustumPlanes[4][3] = comboMatrix[3][3] + comboMatrix[2][3];
            // Far
            m_frustumPlanes[5][0] = comboMatrix[3][0] - comboMatrix[2][0];
            m_frustumPlanes[5][1] = comboMatrix[3][1] - comboMatrix[2][1];
            m_frustumPlanes[5][2] = comboMatrix[3][2] - comboMatrix[2][2];
            m_frustumPlanes[5][3] = comboMatrix[3][3] - comboMatrix[2][3];
        }

        bool Camera::testSphere(const glm::vec3& center, float radius) const
        {
            // TODO
            /*
            for (int i = 0; i < 1; i++)
            {
                if (m_frustumPlanes[i][0] * center[0] +
                    m_frustumPlanes[i][1] * center[1] +
                    m_frustumPlanes[i][2] * center[2] + m_frustumPlanes[i][3] + radius < 0.0f)
                {
                    return false;
                }
            }
            */

            return true;
        }

    }

}
