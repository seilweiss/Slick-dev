#pragma once

#include "core/asset.h"
#include "core/assetmanager.h"
#include "render/texture.h"

#include "hiphop/assets/texture_asset.h"

namespace Slick {

    namespace Assets {

        class TextureAsset : public Core::Asset
        {
            Q_OBJECT

        public:
            TextureAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            Render::Texture* texture() { return &m_texture; }

            void setup();
            void bind();
            void unbind();

            virtual void inspect(Inspector::Root* root) override;
            virtual QWidget* createPreview() override;

        private:
            HipHop::TextureAsset m_textureAsset;
            Render::Texture m_texture;
            QString m_info;
        };

        class TextureManager : public Core::AssetManager
        {
            Q_OBJECT

        public:
            TextureManager(Core::Scene* scene) : Core::AssetManager(scene) {}

            void setup();

            virtual bool supports(HipHop::Asset asset) const override { return asset.GetType() == HipHop::AssetType::RWTX; }
            virtual Core::Asset* createAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) { return new TextureAsset(asset, sceneFile); }
        };

    }

}
