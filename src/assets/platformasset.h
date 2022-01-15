#pragma once

#include "assets/entasset.h"
#include "assets/motionasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/platform_asset.h"

namespace Slick {

    namespace Assets {

        class PlatformAsset : public EntAsset
        {
            Q_OBJECT

        public:
            PlatformAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::PlatformAsset* serializer() { return &m_platform; }

            virtual void setup() override;
            virtual void update() override;
            virtual void render() override;
            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::PlatformAsset m_platform;
            MotionAsset* m_motion;
        };

        class PlatformManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            PlatformManager(Core::Scene* scene) : AssetManager(scene) {}

            void setup();
            void update();
            void render();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::PLAT; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new PlatformAsset(asset, sceneFile); }
        };

    }

}
