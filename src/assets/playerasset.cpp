#include "assets/playerasset.h"

#include "assets/lightkitasset.h"
#include "core/scene.h"

namespace Slick {

    namespace Assets {

        PlayerAsset::PlayerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_player(asset)
        {
            setSerializer(&m_player);
        }

        void PlayerAsset::setup()
        {
            EntAsset::setup();

            setLightKit(qobject_cast<Assets::LightKitAsset*>(scene()->assetById(m_player.lightKitID)));
        }

        void PlayerAsset::update()
        {
            EntAsset::update();
        }

        void PlayerAsset::render()
        {
            EntAsset::render();
        }

        void PlayerAsset::inspect(Inspector::Root* root)
        {
            EntAsset::inspect(root);

            auto playerGroup = root->addGroup("player", tr("Player"));
            auto lightKitProp = playerGroup->addAssetInput("lightKit", tr("LightKit"), &m_player.lightKitID, scene());

            lightKitProp->setHelpText(tr("The player's LightKit."));

            connect(lightKitProp, &Inspector::Property::dataChanged, this, &PlayerAsset::makeDirty);

            inspectEntity(root);
            inspectLinks(root);
        }

        void PlayerManager::setup()
        {
            for (auto asset : assets())
            {
                ((PlayerAsset*)asset)->setup();
            }
        }

        void PlayerManager::update()
        {
            for (auto asset : assets())
            {
                ((PlayerAsset*)asset)->update();
            }
        }

        void PlayerManager::render()
        {
            for (auto asset : assets())
            {
                ((PlayerAsset*)asset)->render();
            }
        }

    }

}
