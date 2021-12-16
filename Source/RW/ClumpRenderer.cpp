#include "RW/ClumpRenderer.h"

#include "rws_core.h"
#include "rws_world.h"

namespace Slick {

    ClumpRenderer::ClumpRenderer(QObject* parent) :
        QObject(parent),
        m_clump(nullptr)
    {
    }

    void ClumpRenderer::setClump(Rws::Clump* clump)
    {
        m_clump = clump;

        for (AtomicRenderer* renderer : m_atomRenderers)
        {
            delete renderer;
        }

        for (GeometryRenderer* renderer : m_geomRenderers)
        {
            delete renderer;
        }

        m_atomRenderers.clear();
        m_geomRenderers.clear();
        m_frames.clear();

        if (!clump)
        {
            return;
        }

        const auto& rwframes = clump->GetFrameList()->GetStruct()->frames;
        auto rwgeoms = clump->GetGeometryList()->GetGeometries();
        auto rwatoms = clump->GetAtomics();

        m_frames.reserve(rwframes.size());
        m_geomRenderers.reserve(rwgeoms.size());
        m_atomRenderers.reserve(rwatoms.size());

        for (const Rws::Frame& rwframe : rwframes)
        {
            Frame frame;
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
            GeometryRenderer* renderer = new GeometryRenderer(this);
            renderer->setGeometry(rwgeom);

            m_geomRenderers.append(renderer);
        }

        for (Rws::Atomic* rwatom : rwatoms)
        {
            Rws::AtomicStruct* atomStruct = rwatom->GetStruct();
            AtomicRenderer* renderer = new AtomicRenderer(this);
            renderer->setAtomic(rwatom);
            renderer->setGeometryRenderer(m_geomRenderers[atomStruct->geomIndex]);
            renderer->setFrame(&m_frames[atomStruct->frameIndex]);

            m_atomRenderers.append(renderer);
        }
    }

    void ClumpRenderer::render(RenderContext* context)
    {
        for (AtomicRenderer* atomRenderer : m_atomRenderers)
        {
            atomRenderer->render(context);
        }
    }

}
