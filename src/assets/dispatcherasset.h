#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/dispatcher_asset.h"

namespace Slick {

    namespace Assets {

        class DispatcherAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            DispatcherAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::DispatcherAsset m_dispatcher;
        };

        class DispatcherManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            DispatcherManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::DPAT; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new DispatcherAsset(asset, sceneFile); }
        };

    }

}
