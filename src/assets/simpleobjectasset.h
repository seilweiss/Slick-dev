#pragma once

#include "assets/entasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/simple_obj_asset.h"

namespace Slick {

    namespace Assets {

        class SimpleObjectAsset : public EntAsset
        {
            Q_OBJECT

        public:
            SimpleObjectAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::SimpleObjAsset m_simpleObj;
        };

        class SimpleObjectManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            SimpleObjectManager(Core::Scene* scene) : AssetManager(scene) {}

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::SIMP; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new SimpleObjectAsset(asset, sceneFile); }
        };

    }

}
