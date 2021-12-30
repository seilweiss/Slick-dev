#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/text_asset.h"

namespace Slick {

    namespace Assets {

        class TextAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            TextAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::TextAsset m_text;
        };

        class TextManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            TextManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::TEXT; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new TextAsset(asset, sceneFile); }
        };

    }

}
