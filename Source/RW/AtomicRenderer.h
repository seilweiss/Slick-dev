#pragma once

#include "RW/GeometryRenderer.h"
#include "RW/Frame.h"

namespace Rws {

    class Atomic;

}

namespace Slick {

    class AtomicRenderer : public QObject
    {
        Q_OBJECT

    public:
        AtomicRenderer(QObject* parent = nullptr);

        Rws::Atomic* atomic() const { return m_atomic; }
        void setAtomic(Rws::Atomic* atomic);

        GeometryRenderer* geometryRenderer() const { return m_geomRenderer; }
        void setGeometryRenderer(GeometryRenderer* renderer) { m_geomRenderer = renderer; }

        Frame* frame() const { return m_frame; }
        void setFrame(Frame* frame) { m_frame = frame; }

        bool visible() const { return m_visible; }
        void setVisible(bool visible) { m_visible = visible; }

        void render(RenderContext* context);

        bool cull(RenderContext* context);

    private:
        Rws::Atomic* m_atomic;
        GeometryRenderer* m_geomRenderer;
        Frame* m_frame;
        bool m_visible;
    };

}
