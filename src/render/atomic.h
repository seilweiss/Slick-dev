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
            void setGeometry(Geometry* geometry);

            Frame* frame() const { return m_frame; }
            void setFrame(Frame* frame) { m_frame = frame; }

            glm::vec3 boundingSphereCenter() const { return m_boundingSphereCenter; }
            void setBoundingSphereCenter(const glm::vec3& center) { m_boundingSphereCenter = center; }

            float boundingSphereRadius() const { return m_boundingSphereRadius; }
            void setBoundingSphereRadius(float radius) { m_boundingSphereRadius = radius; }

            glm::vec3 worldBoundingSphereCenter() const;
            float worldBoundingSphereRadius() const;

            bool visible() const { return m_visible; }
            void setVisible(bool visible) { m_visible = visible; }

            void render();

            bool cull() const;

        private:
            Context* m_context;
            Rws::Atomic* m_data;
            Geometry* m_geometry;
            Frame* m_frame;
            glm::vec3 m_boundingSphereCenter;
            float m_boundingSphereRadius;

            bool m_visible;
        };

    }

}
