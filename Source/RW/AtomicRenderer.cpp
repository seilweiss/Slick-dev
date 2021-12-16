#include "RW/AtomicRenderer.h"

#include "rws_core.h"
#include "rws_world.h"

#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    AtomicRenderer::AtomicRenderer(QObject* parent) :
        QObject(parent),
        m_atomic(nullptr),
        m_geomRenderer(nullptr),
        m_frame(nullptr)
    {
    }

    void AtomicRenderer::setAtomic(Rws::Atomic* atomic)
    {
        m_atomic = atomic;

        if (!atomic)
        {
            return;
        }

        Rws::AtomicStruct* atomStruct = atomic->GetStruct();

        if (atomStruct)
        {
            m_visible = (atomStruct->flags & Rws::AtomicStruct::RENDER) != 0;
        }
    }

    void AtomicRenderer::render(RenderContext* context)
    {
        if (!m_visible)
        {
            return;
        }

        if (!m_geomRenderer)
        {
            return;
        }

        if (m_frame)
        {
            m_frame->bind(context);
        }

        m_geomRenderer->render(context);

        if (m_frame)
        {
            m_frame->unbind(context);
        }

        context->stats().atomicCount++;
    }

    bool AtomicRenderer::cull(RenderContext* context)
    {
        // TODO
        return false;
    }

}
