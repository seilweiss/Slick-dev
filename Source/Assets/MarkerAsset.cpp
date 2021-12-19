#include "Assets/MarkerAsset.h"

namespace Slick {

    namespace Assets {

        MarkerAsset::MarkerAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_marker(asset)
        {
            setEditor(&m_marker);
        }

        void MarkerAsset::inspect(Inspector* inspector)
        {
            Asset::inspect(inspector);

            auto transformGroup = inspector->addGroup("transform");
            auto posProp = transformGroup->addVectorInput("position", (Vector3*)&m_marker.pos);

            connect(posProp, &InspectorProperty::dataChanged, this, &MarkerAsset::makeDirty);
        }

    }

}
