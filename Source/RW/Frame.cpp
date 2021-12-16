#include "RW/Frame.h"

#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    Frame::Frame() :
        m_parent(nullptr),
        m_mat(1.0f)
    {
    }

    void Frame::bind(RenderContext* context)
    {
        if (m_parent)
        {
            m_parent->bind(context);
        }

        context->glMatrixMode(GL_MODELVIEW);
        context->glPushMatrix();
        context->glMultMatrixf(glm::value_ptr(m_mat));
    }

    void Frame::unbind(RenderContext* context)
    {
        context->glMatrixMode(GL_MODELVIEW);
        context->glPopMatrix();

        if (m_parent)
        {
            m_parent->unbind(context);
        }
    }

}
