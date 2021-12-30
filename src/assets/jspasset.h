#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"
#include "render/clump.h"

#include "hiphop/assets/jsp_asset.h"

namespace Slick {

    namespace Assets {

        class JSPAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            JSPAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            void setup();
            void render();

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::JSPAsset m_jsp;
            Render::Clump m_clump;
            QList<JSPAsset*> m_jspAssets;
        };

        class JSPManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            JSPManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::JSP; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new JSPAsset(asset, sceneFile); }
        };

    }

}
