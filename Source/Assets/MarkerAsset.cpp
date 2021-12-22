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

            auto transformGroup = inspector->addGroup("transform", tr("Transform"));
            auto posProp = transformGroup->addVectorInput("position", tr("Position"), (Vector3*)&m_marker.pos);

            posProp->setHelpText(tr("The marker's position."));

            connect(posProp, &InspectorProperty::dataChanged, this, &MarkerAsset::makeDirty);
        }

    }

}
