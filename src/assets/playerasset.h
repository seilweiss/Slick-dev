#pragma once

#include "assets/entasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/player_asset.h"

namespace Slick {

    namespace Assets {

        class PlayerAsset : public EntAsset
        {
            Q_OBJECT

        public:
            PlayerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::PlayerAsset m_player;
        };

        class PlayerManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            PlayerManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::PLYR; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new PlayerAsset(asset, sceneFile); }
        };

    }

}
