#pragma once

#include "RW/AtomicRenderer.h"

namespace Rws {

    class Clump;

}

namespace Slick {

    class ClumpRenderer : public QObject
    {
        Q_OBJECT

    public:
        ClumpRenderer(QObject* parent = nullptr);

        Rws::Clump* clump() const { return m_clump; }
        void setClump(Rws::Clump* clump);

        const QList<AtomicRenderer*>& atomicRenderers() const { return m_atomRenderers; }

        void render(RenderContext* context);

    private:
        Rws::Clump* m_clump;
        QList<AtomicRenderer*> m_atomRenderers;
        QList<GeometryRenderer*> m_geomRenderers;
        QList<Frame> m_frames;
    };

}
