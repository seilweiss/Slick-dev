#include "Assets/EnvAsset.h"

#include "Assets/JSPAsset.h"
#include "Core/Scene.h"

namespace Slick {

    namespace Assets {

        EnvAsset::EnvAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_env(asset),
            m_setup(false)
        {
            m_env.Load();
        }

        void EnvAsset::doSave()
        {
            m_env.Save();
        }

        void EnvAsset::render(RenderContext* context)
        {
            if (!m_setup)
            {
                setup();
            }

            if (m_jspInfo)
            {
                m_jspInfo->render(context);
            }
        }

        void EnvAsset::setup()
        {
            m_jspInfo = qobject_cast<JSPAsset*>(scene()->asset(m_env.bspAssetID));

            m_setup = true;
        }

    }

}
