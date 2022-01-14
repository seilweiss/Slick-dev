#pragma once

#include "assets/entasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/trigger_asset.h"

namespace Slick {

    namespace Assets {

        class TriggerAsset : public EntAsset
        {
            Q_OBJECT

        public:
            TriggerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::TriggerAsset m_trigger;
        };

        class TriggerManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            TriggerManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::TRIG; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new TriggerAsset(asset, sceneFile); }
        };

    }

}
