#pragma once

#include "assets/entasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/egen_asset.h"

namespace Slick {

    namespace Assets {

        class EGenAsset : public EntAsset
        {
            Q_OBJECT

        public:
            EGenAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::EGenAsset* serializer() { return &m_egen; }

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::EGenAsset m_egen;
        };

        class EGenManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            EGenManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::EGEN; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new EGenAsset(asset, sceneFile); }
        };

    }

}
