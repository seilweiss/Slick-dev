#pragma once

#include "Render/Context.h"

#include <QObject>

#include <glm/glm.hpp>

namespace Rws {

    class Geometry;

}

namespace Slick {

    namespace Render {

        class Geometry : public QObject
        {
            Q_OBJECT

        public:
            Geometry(QObject* parent = nullptr);

            Rws::Geometry* data() const { return m_data; }
            void setData(Rws::Geometry* data);

            void render(Context& context);

        private:
            Rws::Geometry* m_data;
            QVector<glm::vec3> m_vertices;
            QVector<glm::vec3> m_normals;
            QVector<glm::vec4> m_colors;
            QVector<glm::vec2> m_uvs;
            QVector<glm::uint16> m_indices;
        };

    }

}
