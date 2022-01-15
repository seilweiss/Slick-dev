#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/marker_asset.h"

namespace Slick {

    namespace Assets {

        class MarkerAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            MarkerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::MarkerAsset* serializer() { return &m_marker; }

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::MarkerAsset m_marker;
        };

        class MarkerManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            MarkerManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::MRKR; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new MarkerAsset(asset, sceneFile); }
        };

    }

}
