#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/env_asset.h"

namespace Slick {

    namespace Assets {

        class JSPAsset;
        class LightKitAsset;

        class EnvAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            EnvAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::EnvAsset* serializer() { return &m_env; }

            JSPAsset* jspInfo() const { return m_jspInfo; }
            LightKitAsset* objectLightKit() const { return m_objLightKit; }

            void setup();
            void render();

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::EnvAsset m_env;
            JSPAsset* m_jspInfo;
            LightKitAsset* m_objLightKit;
        };

        class EnvManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            EnvManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::ENV; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new EnvAsset(asset, sceneFile); }
        };

    }

}
