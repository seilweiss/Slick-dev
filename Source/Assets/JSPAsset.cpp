#include "Assets/JSPAsset.h"

#include <QDebug>

namespace Slick {

    namespace Assets {

        JSPAsset::JSPAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_clump(new Render::Clump(this)),
            m_jsp(asset)
        {
            m_jsp.Load();

            m_clump->setData(m_jsp.GetClump());
        }

        void JSPAsset::render(Render::Context& context)
        {
            m_clump->render(context);
        }

    }

}
