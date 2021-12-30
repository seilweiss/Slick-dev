#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/anim_list_asset.h"

namespace Slick {

    namespace Assets {

        class AnimListAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            AnimListAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::AnimListAsset m_animList;
        };

        class AnimListManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            AnimListManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::ALST; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new AnimListAsset(asset, sceneFile); }
        };

    }

}
