#include "Assets/ModelAsset.h"

#include "Core/Scene.h"

namespace Slick {

    namespace Assets {

        ModelAsset::ModelAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_model(asset),
            m_clumpRenderer(nullptr)
        {
            setEditor(&m_model);
        }

        void ModelAsset::inspect(Inspector* inspector)
        {
            Asset::inspect(inspector);

            inspector->addGroup("model", tr("Model"));
        }

        void ModelAsset::setup()
        {
            m_clumpRenderer = new ClumpRenderer(this);
            m_clumpRenderer->setClump(m_model.GetClump());
        }

        void ModelAsset::render(RenderContext* context)
        {
            context->glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
            context->glEnable(GL_DEPTH_TEST);

            m_clumpRenderer->render(context);

            context->glPopAttrib();
        }

    }

}
