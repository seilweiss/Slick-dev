#pragma once

#include "assets/baseasset.h"
#include "render/clump.h"

#include "hiphop/core/ent_asset.h"

namespace Slick {

    namespace Assets {

        class ModelAsset;
        class EnvAsset;
        class LightKitAsset;

        class EntAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            EntAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::EntAsset* editor() const { return m_ent; }
            void setEditor(HipHop::EntAsset* editor) { BaseAsset::setEditor(editor); m_ent = editor; }

            Assets::ModelAsset* model() const { return m_model; }

            Render::Clump* clump() { return &m_clump; }
            const Render::Clump* clump() const { return &m_clump; }

            bool renderEnabled() const { return m_renderEnabled; }
            void setRenderEnabled(bool enabled) { m_renderEnabled = enabled; }

            virtual void setup();
            virtual void update();
            virtual void render();

            virtual void inspect(Inspector::Root* root) override;

        protected:
            void inspectEntity(Inspector::Root* root);
            void setLightKit(Assets::LightKitAsset* lightKit) { m_lightKit = lightKit; }
            void setColor(const Core::ColorF& color) { m_color = color; }

        private:
            HipHop::EntAsset m_entDefault;
            HipHop::EntAsset* m_ent;
            Assets::ModelAsset* m_model;
            Render::Clump m_clump;
            Assets::EnvAsset* m_env;
            Assets::LightKitAsset* m_lightKit;
            Core::ColorF m_color;
            bool m_renderEnabled;
        };

    }

}
