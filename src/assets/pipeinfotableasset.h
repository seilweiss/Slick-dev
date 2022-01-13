#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/pipe_info_table_asset.h"

namespace Slick {

    namespace Assets {

        class PipeInfoTableAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            PipeInfoTableAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::PipeInfoTableAsset* data() { return &m_pipt; }

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::PipeInfoTableAsset m_pipt;
        };

        class PipeInfoTableManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            PipeInfoTableManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::PIPT; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new PipeInfoTableAsset(asset, sceneFile); }
        };

    }

}
