#pragma once

#include "assets/baseasset.h"
#include "core/assetmanager.h"

#include "hiphop/assets/fog_asset.h"

namespace Slick {

    namespace Assets {

        class FogAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            FogAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            void apply();

            virtual void inspect(Inspector::Root* root) override;

        private:
            HipHop::FogAsset m_fog;
        };

        class FogManager : public Core::AssetManager
        {
            Q_OBJECT
            Q_PROPERTY(Assets::FogAsset* previewFog READ previewFog WRITE setPreviewFog NOTIFY previewFogChanged)

        public:
            FogManager(Core::Scene* scene) : Core::AssetManager(scene), m_previewFog(nullptr), m_enabled(true) {}

            Assets::FogAsset* previewFog() const { return m_previewFog; }
            void setPreviewFog(Assets::FogAsset* fog);

            void setup();
            void apply();

            bool enabled() const { return m_enabled; }
            void setEnabled(bool enabled) { m_enabled = enabled; }

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::FOG; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new FogAsset(asset, sceneFile); }

        signals:
            void previewFogChanged(Assets::FogAsset* fog);

        private:
            FogAsset* m_previewFog;
            bool m_enabled;
        };

    }

}
