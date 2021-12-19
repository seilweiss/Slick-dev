#pragma once

#include "Core/RenderContext.h"

#include <glm/glm.hpp>

#include <QObject>

namespace Rws {

    class Geometry;

}

namespace Slick {

    class GeometryRenderer : public QObject
    {
        Q_OBJECT

    public:
        GeometryRenderer(QObject* parent = nullptr);

        Rws::Geometry* geometry() const { return m_geometry; }
        void setGeometry(Rws::Geometry* geometry);

        void render(RenderContext* context);

    private:
        Rws::Geometry* m_geometry;
        QList<glm::vec3> m_vertices;
        QList<glm::vec3> m_normals;
        QList<glm::vec4> m_colors;
        QList<glm::vec2> m_uvs;
        QList<glm::uint16> m_indices;
    };

}
