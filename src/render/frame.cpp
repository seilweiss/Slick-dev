#include "render/frame.h"

#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    namespace Render {

        Frame::Frame(Context* context) :
            m_context(context),
            m_parent(nullptr),
            m_mat(1.0f)
        {
        }

        void Frame::bind()
        {
            if (m_parent)
            {
                m_parent->bind();
            }

            m_context->glMatrixMode(GL_MODELVIEW);
            m_context->glPushMatrix();
            m_context->glMultMatrixf(glm::value_ptr(m_mat));
        }

        void Frame::unbind()
        {
            m_context->glMatrixMode(GL_MODELVIEW);
            m_context->glPopMatrix();

            if (m_parent)
            {
                m_parent->unbind();
            }
        }

    }

}
