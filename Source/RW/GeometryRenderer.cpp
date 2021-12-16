#include "RW/GeometryRenderer.h"

#include "rws_core.h"
#include "rws_world.h"

#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    GeometryRenderer::GeometryRenderer(QObject* parent) :
        QObject(parent),
        m_geometry(nullptr)
    {
    }

    void GeometryRenderer::setGeometry(Rws::Geometry* geometry)
    {
        m_geometry = geometry;
        m_vertices.clear();
        m_normals.clear();
        m_colors.clear();
        m_uvs.clear();
        m_indices.clear();

        if (!geometry)
        {
            return;
        }

        Rws::GeometryStruct* geomStruct = geometry->GetStruct();

        if (geomStruct->IsNative())
        {
            qDebug("Geometry is native");
            return;
        }

        Rws::MorphTarget* morph = &geomStruct->morphTargets[0];

        {
            m_vertices.reserve(geomStruct->numVertices);

            for (auto& v : morph->verts)
            {
                m_vertices.push_back({ v.x, v.y, v.z });
            }
        }

        if (geomStruct->HasNormals())
        {
            m_normals.reserve(geomStruct->numVertices);

            for (auto& n : morph->normals)
            {
                m_normals.push_back({ n.x, n.y, n.z });
            }
        }

        if (geomStruct->HasColors())
        {
            m_colors.reserve(geomStruct->numVertices);

            for (auto& c : geomStruct->preLitLum)
            {
                m_colors.push_back({ c.red / 255.0f, c.green / 255.0f, c.blue / 255.0f, c.alpha / 255.0f });
            }
        }

        if (geomStruct->GetNumTexCoordSets() != 0)
        {
            m_uvs.reserve(geomStruct->numVertices);

            for (auto& t : geomStruct->texCoords[0])
            {
                m_uvs.push_back({ t.u, t.v });
            }
        }

        {
            m_indices.reserve(geomStruct->triangles.size() * 3);

            for (auto& t : geomStruct->triangles)
            {
                m_indices.push_back(t.vertIndex[0]);
                m_indices.push_back(t.vertIndex[1]);
                m_indices.push_back(t.vertIndex[2]);
            }
        }
    }

    void GeometryRenderer::render(RenderContext* context)
    {
        if (!m_geometry)
        {
            return;
        }

        context->glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

        context->glDisableClientState(GL_EDGE_FLAG_ARRAY);
        context->glDisableClientState(GL_INDEX_ARRAY);

        if (!m_normals.empty())
        {
            context->glEnableClientState(GL_NORMAL_ARRAY);
            context->glNormalPointer(GL_FLOAT, 0, glm::value_ptr(m_normals[0]));
        }
        else
        {
            context->glDisableClientState(GL_NORMAL_ARRAY);
        }

        if (!m_colors.empty())
        {
            context->glEnableClientState(GL_COLOR_ARRAY);
            context->glColorPointer(4, GL_FLOAT, 0, glm::value_ptr(m_colors[0]));
        }
        else
        {
            context->glDisableClientState(GL_COLOR_ARRAY);
        }

        if (!m_uvs.empty())
        {
            context->glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            context->glTexCoordPointer(2, GL_FLOAT, 0, glm::value_ptr(m_uvs[0]));
        }
        else
        {
            context->glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        context->glEnableClientState(GL_VERTEX_ARRAY);
        context->glVertexPointer(3, GL_FLOAT, 0, glm::value_ptr(m_vertices[0]));

        context->glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, &m_indices[0]);

        context->glPopClientAttrib();
    }

}
