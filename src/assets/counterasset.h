#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/counter_asset.h"

namespace Slick {

    namespace Assets {

        class CounterAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            CounterAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::CounterAsset m_counter;
        };

        class CounterManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            CounterManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::CNTR; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new CounterAsset(asset, sceneFile); }
        };

    }

}
