#include "Render/Geometry.h"

#include "Render/Viewport.h"

#include "rws_core.h"
#include "rws_world.h"

#include <QDebug>

namespace Slick {

    namespace Render {

        Geometry::Geometry(QObject* parent) :
            QObject(parent),
            m_data(nullptr)
        {
        }

        void Geometry::setData(Rws::Geometry* data)
        {
            m_data = data;
            m_vertices.clear();
            m_normals.clear();
            m_colors.clear();
            m_uvs.clear();
            m_indices.clear();

            Rws::GeometryStruct* rwGeomStruct = data->GetStruct();

            if (rwGeomStruct->IsNative())
            {
                qDebug() << "Geometry is native";
                return;
            }

            Rws::MorphTarget* rwMorph = &rwGeomStruct->morphTargets[0];

            {
                m_vertices.reserve(rwGeomStruct->numVertices);

                for (auto& v : rwMorph->verts)
                {
                    m_vertices.push_back({ v.x, v.y, v.z });
                }
            }

            if (rwGeomStruct->HasNormals())
            {
                m_normals.reserve(rwGeomStruct->numVertices);

                for (auto& n : rwMorph->normals)
                {
                    m_normals.push_back({ n.x, n.y, n.z });
                }
            }

            if (rwGeomStruct->HasColors())
            {
                m_colors.reserve(rwGeomStruct->numVertices);

                for (auto& c : rwGeomStruct->preLitLum)
                {
                    m_colors.push_back({ c.red / 255.0f, c.green / 255.0f, c.blue / 255.0f, c.alpha / 255.0f });
                }
            }

            if (rwGeomStruct->GetNumTexCoordSets() != 0)
            {
                m_uvs.reserve(rwGeomStruct->numVertices);

                for (auto& t : rwGeomStruct->texCoords[0])
                {
                    m_uvs.push_back({ t.u, t.v });
                }
            }

            {
                m_indices.reserve(rwGeomStruct->triangles.size() * 3);

                for (auto& t : rwGeomStruct->triangles)
                {
                    m_indices.push_back(t.vertIndex[2]);
                    m_indices.push_back(t.vertIndex[1]);
                    m_indices.push_back(t.vertIndex[0]);
                }
            }
        }

        void Geometry::render(Context& context)
        {
            Rws::GeometryStruct* rwGeomStruct = m_data->GetStruct();

            if (rwGeomStruct->IsNative())
            {
                return;
            }

            Rws::MorphTarget* rwMorph = &rwGeomStruct->morphTargets[0];

            context.viewport->glBegin(GL_TRIANGLE_STRIP);

            for (int i = 0; i < rwGeomStruct->numVertices; i++)
            {
                if (rwGeomStruct->HasNormals())
                {
                    context.viewport->glNormal3f(rwMorph->normals[i].x, rwMorph->normals[i].y, rwMorph->normals[i].z);
                }

                if (rwGeomStruct->HasColors())
                {
                    context.viewport->glColor4i(rwGeomStruct->preLitLum[i].red, rwGeomStruct->preLitLum[i].green, rwGeomStruct->preLitLum[i].blue, rwGeomStruct->preLitLum[i].alpha);
                }

                if (rwGeomStruct->GetNumTexCoordSets() != 0)
                {
                    context.viewport->glTexCoord2f(rwGeomStruct->texCoords[0][i].u, rwGeomStruct->texCoords[0][i].v);
                }

                context.viewport->glVertex3f(rwMorph->verts[i].x, rwMorph->verts[i].y, rwMorph->verts[i].z);
            }

            context.viewport->glEnd();
        }

    }

}
