#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/cond_asset.h"

namespace Slick {

    namespace Assets {

        class ConditionalAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            ConditionalAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::CondAsset* serializer() { return &m_cond; }

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::CondAsset m_cond;
        };

        class ConditionalManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            ConditionalManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::COND; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new ConditionalAsset(asset, sceneFile); }
        };

    }

}
