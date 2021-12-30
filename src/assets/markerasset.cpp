#include "assets/markerasset.h"

namespace Slick {

    namespace Assets {

        MarkerAsset::MarkerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_marker(asset)
        {
            setEditor(&m_marker);
        }

        void MarkerAsset::inspect(Inspector::Root* root)
        {
            Asset::inspect(root);

            auto transformGroup = root->addGroup("transform", tr("Transform"));
            auto posProp = transformGroup->addVectorInput("position", tr("Position"), (Core::Vector3*)&m_marker.pos);

            posProp->setHelpText(tr("The marker's position."));

            connect(posProp, &Inspector::Property::dataChanged, this, &MarkerAsset::makeDirty);
        }

    }

}
