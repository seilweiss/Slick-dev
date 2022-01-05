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
            m_frame(nullptr)
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
