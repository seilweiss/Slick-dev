#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/timer_asset.h"

namespace Slick {

    namespace Assets {

        class TimerAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            TimerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::TimerAsset m_timer;
        };

        class TimerManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            TimerManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::TIMR; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new TimerAsset(asset, sceneFile); }
        };

    }

}
