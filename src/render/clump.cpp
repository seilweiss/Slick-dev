#include "render/clump.h"

#include "rws_core.h"
#include "rws_world.h"

namespace Slick {

    namespace Render {

        Clump::Clump(Context* context, Rws::Clump* data) :
            m_context(context),
            m_data(nullptr)
        {
            setData(data);
        }

        void Clump::setData(Rws::Clump* data)
        {
            m_data = data;

            m_atomics.clear();
            m_geoms.clear();
            m_frames.clear();

            if (!m_data)
            {
                return;
            }

            const auto& rwframes = m_data->GetFrameList()->GetStruct()->frames;
            auto rwgeoms = m_data->GetGeometryList()->GetGeometries();
            auto rwatoms = m_data->GetAtomics();

            m_frames.reserve(rwframes.size());
            m_geoms.reserve(rwgeoms.size());
            m_atomics.reserve(rwatoms.size());

            for (const Rws::Frame& rwframe : rwframes)
            {
                Frame frame(m_context);
                glm::mat4 mat;

                mat[0][0] = rwframe.right.x;
                mat[0][1] = rwframe.right.y;
                mat[0][2] = rwframe.right.z;
                mat[0][3] = 0.0f;
                mat[1][0] = rwframe.up.x;
                mat[1][1] = rwframe.up.y;
                mat[1][2] = rwframe.up.z;
                mat[1][3] = 0.0f;
                mat[2][0] = rwframe.at.x;
                mat[2][1] = rwframe.at.y;
                mat[2][2] = rwframe.at.z;
                mat[2][3] = 0.0f;
                mat[3][0] = rwframe.pos.x;
                mat[3][1] = rwframe.pos.y;
                mat[3][2] = rwframe.pos.z;
                mat[3][3] = 1.0f;

                frame.setMatrix(mat);

                if (rwframe.parentIndex >= 0)
                {
                    frame.setParent(&m_frames[rwframe.parentIndex]);
                }

                m_frames.append(frame);
            }

            for (Rws::Geometry* rwgeom : rwgeoms)
            {
                Geometry geom(m_context, rwgeom);

                m_geoms.append(geom);
            }

            for (Rws::Atomic* rwatom : rwatoms)
            {
                Rws::AtomicStruct* atomStruct = rwatom->GetStruct();

                Atomic atomic(m_context, rwatom);
                atomic.setGeometry(&m_geoms[atomStruct->geomIndex]);
                atomic.setFrame(&m_frames[atomStruct->frameIndex]);

                m_atomics.append(atomic);
            }
        }

        void Clump::render()
        {
            for (Atomic& atomic : m_atomics)
            {
                atomic.render();
            }
        }

    }

}
