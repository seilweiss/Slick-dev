#include "Assets/PlayerAsset.h"

#include "Assets/LightKitAsset.h"
#include "Core/Scene.h"

namespace Slick {

    namespace Assets {

        PlayerAsset::PlayerAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_player(asset)
        {
            setEditor(&m_player);
        }

        void PlayerAsset::setup()
        {
            setLightKit((Assets::LightKitAsset*)scene()->asset(m_player.lightKitID));
        }

        void PlayerAsset::inspect(Inspector* inspector)
        {
            EntAsset::inspect(inspector);

            auto playerGroup = inspector->addGroup("player", tr("Player"));
            auto lightKitProp = playerGroup->addAssetInput("lightKit", tr("LightKit"), &m_player.lightKitID, scene());

            lightKitProp->setHelpText(tr("The player's LightKit."));

            connect(lightKitProp, &InspectorProperty::dataChanged, this, &PlayerAsset::makeDirty);

            inspectEntity(inspector);
            inspectLinks(inspector);
        }

    }

}
