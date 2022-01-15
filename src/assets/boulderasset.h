#pragma once

#include "assets/entasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/boulder_asset.h"

namespace Slick {

    namespace Assets {

        class BoulderAsset : public EntAsset
        {
            Q_OBJECT

        public:
            BoulderAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::BoulderAsset* serializer() { return &m_boulder; }

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::BoulderAsset m_boulder;
        };

        class BoulderManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            BoulderManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::BOUL; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new BoulderAsset(asset, sceneFile); }
        };

    }

}
