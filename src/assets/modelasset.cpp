#include "assets/modelasset.h"

#include "core/scene.h"

namespace Slick {

    namespace Assets {

        ModelAsset::ModelAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_model(asset),
            m_clump(Render::Clump(scene()->renderContext()))
        {
            setEditor(&m_model);
        }

        void ModelAsset::setup()
        {
            m_clump.setData(m_model.GetClump());

            scene()->setupClump(&m_clump);
        }

        void ModelAsset::render()
        {
            scene()->renderContext()->glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
            scene()->renderContext()->glEnable(GL_DEPTH_TEST);

            m_clump.render();

            scene()->renderContext()->glPopAttrib();
        }

        void ModelAsset::inspect(Inspector::Root* root)
        {
            Core::Asset::inspect(root);

            root->addGroup("model", tr("Model"));
        }

        void ModelManager::setup()
        {
            for (auto asset : assets())
            {
                ((ModelAsset*)asset)->setup();
            }
        }

    }

}
