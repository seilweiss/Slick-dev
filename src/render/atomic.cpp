#include "render/atomic.h"

#include "render/context.h"

#include "rws_core.h"
#include "rws_world.h"

#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    namespace Render {

        Atomic::Atomic(Context* context, Rws::Atomic* data) :
            m_context(context),
            m_data(nullptr),
            m_geometry(nullptr),
            m_frame(nullptr),
            m_boundingSphereCenter(0.0f),
            m_boundingSphereRadius(0.0f),
            m_visible(true)
        {
            setData(data);
        }

        void Atomic::setData(Rws::Atomic* data)
        {
            m_data = data;

            if (!m_data)
            {
                return;
            }

            Rws::AtomicStruct* atomStruct = m_data->GetStruct();

            if (atomStruct)
            {
                m_visible = (atomStruct->flags & Rws::AtomicStruct::RENDER) != 0;
            }
        }

        void Atomic::setGeometry(Geometry* geometry)
        {
            m_geometry = geometry;

            if (geometry)
            {
                Rws::GeometryStruct* geomStruct = geometry->data()->GetStruct();

                if (geomStruct)
                {
                    Rws::Sphere& sph = geomStruct->morphTargets[0].boundingSphere;

                    m_boundingSphereCenter = glm::vec3(sph.center.x, sph.center.y, sph.center.z);
                    m_boundingSphereRadius = sph.radius;
                }
            }
        }

        glm::vec3 Atomic::worldBoundingSphereCenter() const
        {
            glm::vec3 center = m_boundingSphereCenter;

            if (m_frame)
            {
                center = glm::vec3(glm::vec4(center, 0.0f) * m_frame->matrix());
            }

            return center;
        }

        // RpAtomicGetWorldBoundingSphere
        float Atomic::worldBoundingSphereRadius() const
        {
            float radius = m_boundingSphereRadius;

            if (m_frame)
            {
                glm::mat4 mat = m_frame->matrix();
                glm::vec3 right = mat[0];
                glm::vec3 up = mat[1];
                glm::vec3 at = mat[2];
                float xscale2 = glm::dot(right, right);
                float yscale2 = glm::dot(up, up);
                float zscale2 = glm::dot(at, at);
                float scale2 = glm::max(glm::max(xscale2, yscale2), zscale2);

                radius *= glm::sqrt(scale2);
            }

            return radius;
        }

        void Atomic::render()
        {
            if (!m_visible)
            {
                return;
            }

            if (!m_geometry)
            {
                return;
            }

            if (m_frame)
            {
                m_frame->bind();
            }

            m_geometry->render();

            if (m_frame)
            {
                m_frame->unbind();
            }

            m_context->stats()->atomicCount++;
        }

        bool Atomic::cull() const
        {
            if (!m_geometry)
            {
                return true;
            }

            if (!m_context->camera())
            {
                return true;
            }

            const Rws::Sphere& sph = m_geometry->data()->GetStruct()->morphTargets[0].boundingSphere;
            glm::vec3 center = glm::vec3(sph.center.x, sph.center.y, sph.center.z);
            float radius = sph.radius;

            if (m_frame)
            {
                center += glm::vec3(m_frame->worldMatrix()[3]);
            }

            return !m_context->camera()->testSphere(center, radius);
        }

    }

}
