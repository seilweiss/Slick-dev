#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/group_asset.h"

namespace Slick {

    namespace Assets {

        class GroupAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            GroupAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::GroupAsset* serializer() { return &m_group; }

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::GroupAsset m_group;
        };

        class GroupManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            GroupManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::GRUP; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new GroupAsset(asset, sceneFile); }
        };

    }

}
