#pragma once

#include "render/geometry.h"
#include "render/frame.h"

namespace Rws { class Atomic; }

namespace Slick {

    namespace Render {

        class Atomic
        {
        public:
            Atomic(Context* context, Rws::Atomic* data = nullptr);

            Rws::Atomic* data() const { return m_data; }
            void setData(Rws::Atomic* data);

            Geometry* geometry() const { return m_geometry; }
            void setGeometry(Geometry* geometry) { m_geometry = geometry; }

            Frame* frame() const { return m_frame; }
            void setFrame(Frame* frame) { m_frame = frame; }

            bool visible() const { return m_visible; }
            void setVisible(bool visible) { m_visible = visible; }

            void render();

            bool cull() const;

        private:
            Context* m_context;
            Rws::Atomic* m_data;
            Geometry* m_geometry;
            Frame* m_frame;
            bool m_visible;
        };

    }

}
