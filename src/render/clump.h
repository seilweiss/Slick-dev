#pragma once

#include "render/atomic.h"

namespace Rws { class Clump; }

namespace Slick {

    namespace Render {

        class Clump
        {
        public:
            Clump(Context* context, Rws::Clump* data = nullptr);

            Rws::Clump* data() const { return m_data; }
            void setData(Rws::Clump* data);

            QList<Atomic>& atomics() { return m_atomics; }
            const QList<Atomic>& atomics() const { return m_atomics; }

            Frame* frame() { return !m_frames.empty() ? &m_frames[0] : nullptr; }
            const Frame* frame() const { return !m_frames.empty() ? &m_frames[0] : nullptr; }

            void render();

        private:
            Context* m_context;
            Rws::Clump* m_data;
            QList<Atomic> m_atomics;
            QList<Geometry> m_geoms;
            QList<Frame> m_frames;
        };

    }

}
