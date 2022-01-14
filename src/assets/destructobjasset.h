#pragma once

#include "assets/entasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/destruct_obj_asset.h"

namespace Slick {

    namespace Assets {

        class DestructObjAsset : public EntAsset
        {
            Q_OBJECT

        public:
            DestructObjAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::DestructObjAsset m_destructObj;
        };

        class DestructObjManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            DestructObjManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::DSTR; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new DestructObjAsset(asset, sceneFile); }
        };

    }

}
