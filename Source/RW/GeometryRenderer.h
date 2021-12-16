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
        QVector<glm::vec3> m_vertices;
        QVector<glm::vec3> m_normals;
        QVector<glm::vec4> m_colors;
        QVector<glm::vec2> m_uvs;
        QVector<glm::uint16> m_indices;
    };

}
