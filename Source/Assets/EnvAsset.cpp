#include "Assets/EnvAsset.h"

#include "Assets/JSPAsset.h"
#include "Core/Scene.h"

namespace Slick {

    namespace Assets {

        EnvAsset::EnvAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_env(asset),
            m_jspInfo(nullptr)
        {
            setEditor(&m_env);
        }

        void EnvAsset::inspect(Inspector* inspector)
        {
            BaseAsset::inspect(inspector);

            inspector->addGroup("environment");

            inspectLinks(inspector);
        }

        void EnvAsset::setup()
        {
            m_jspInfo = qobject_cast<JSPAsset*>(scene()->asset(m_env.bspAssetID));
        }

        void EnvAsset::render(RenderContext* context)
        {
            if (m_jspInfo)
            {
                m_jspInfo->render(context);
            }
        }

    }

}
