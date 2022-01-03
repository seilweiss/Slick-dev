#include "render/geometry.h"

#include "render/context.h"

#include "rws_core.h"
#include "rws_world.h"

#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    namespace Render {

        Geometry::Geometry(Context* context, Rws::Geometry* data) :
            m_context(context),
            m_data(nullptr),
            m_hasAlpha(false)
        {
            setData(data);
        }

        void Geometry::setData(Rws::Geometry* data)
        {
            m_data = data;
            m_vertices.clear();
            m_normals.clear();
            m_colors.clear();
            m_uvs.clear();
            m_materials.clear();
            m_meshes.clear();

            if (!m_data)
            {
                return;
            }

            Rws::GeometryStruct* geomStruct = m_data->GetStruct();

            if (geomStruct->IsNative())
            {
                qDebug("Geometry is native");
                return;
            }

            Rws::MorphTarget* morph = &geomStruct->morphTargets[0];

            if (!morph)
            {
                qDebug("No morph target found");
                return;
            }

            Rws::MaterialList* matList = m_data->GetMaterialList();

            if (!matList)
            {
                qDebug("No material list found");
                return;
            }

            m_materials.reserve(matList->GetMaterialCount());

            for (Rws::Material* rwmat : matList->GetMaterials())
            {
                m_materials.emplace_back(m_context, rwmat);
            }

            m_meshes.resize(m_materials.size());

            {
                m_vertices.reserve(geomStruct->numVertices);

                for (auto& v : morph->verts)
                {
                    m_vertices.emplace_back(v.x, v.y, v.z);
                }
            }

            if (geomStruct->HasNormals())
            {
                m_normals.reserve(geomStruct->numVertices);

                for (auto& n : morph->normals)
                {
                    m_normals.emplace_back(n.x, n.y, n.z);
                }
            }

            if (geomStruct->HasColors())
            {
                m_colors.reserve(geomStruct->numVertices);

                for (auto& c : geomStruct->preLitLum)
                {
                    if (c.alpha < 255)
                    {
                        m_hasAlpha = true;
                    }

                    m_colors.emplace_back(c.red / 255.0f, c.green / 255.0f, c.blue / 255.0f, c.alpha / 255.0f);
                }
            }

            if (geomStruct->GetNumTexCoordSets() != 0)
            {
                m_uvs.reserve(geomStruct->numVertices);

                for (auto& t : geomStruct->texCoords[0])
                {
                    m_uvs.emplace_back(t.u, t.v);
                }
            }

            {
                for (auto& t : geomStruct->triangles)
                {
                    m_meshes[t.matIndex].indices.emplace_back(t.vertIndex[0]);
                    m_meshes[t.matIndex].indices.emplace_back(t.vertIndex[1]);
                    m_meshes[t.matIndex].indices.emplace_back(t.vertIndex[2]);
                }
            }
        }

        void Geometry::render()
        {
            if (!m_data || m_vertices.empty())
            {
                return;
            }

            m_context->glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            m_context->glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
            m_context->glDisableClientState(GL_EDGE_FLAG_ARRAY);
            m_context->glDisableClientState(GL_INDEX_ARRAY);

            if (!m_normals.empty())
            {
                m_context->glEnableClientState(GL_NORMAL_ARRAY);
                m_context->glNormalPointer(GL_FLOAT, 0, glm::value_ptr(m_normals[0]));
            }
            else
            {
                m_context->glDisableClientState(GL_NORMAL_ARRAY);
            }

            if (!m_colors.empty())
            {
                m_context->glEnableClientState(GL_COLOR_ARRAY);
                m_context->glColorPointer(4, GL_FLOAT, 0, glm::value_ptr(m_colors[0]));
            }
            else
            {
                m_context->glDisableClientState(GL_COLOR_ARRAY);
            }

            if (!m_uvs.empty())
            {
                m_context->glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                m_context->glTexCoordPointer(2, GL_FLOAT, 0, glm::value_ptr(m_uvs[0]));
            }
            else
            {
                m_context->glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }

            m_context->glEnableClientState(GL_VERTEX_ARRAY);
            m_context->glVertexPointer(3, GL_FLOAT, 0, glm::value_ptr(m_vertices[0]));

            for (int i = 0; i < m_meshes.size(); i++)
            {
                if (m_hasAlpha)
                {
                    m_context->glEnable(GL_BLEND);
                    m_context->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }

                m_materials[i].bind();

                m_context->glDrawElements(GL_TRIANGLES, m_meshes[i].indices.size(), GL_UNSIGNED_SHORT, &m_meshes[i].indices[0]);

                m_materials[i].unbind();
            }

            m_context->glPopClientAttrib();
            m_context->glPopAttrib();

            m_context->stats()->triangleCount += (int)m_data->GetStruct()->triangles.size();
        }

    }

}
