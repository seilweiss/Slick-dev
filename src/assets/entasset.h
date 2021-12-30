#pragma once

#include "assets/baseasset.h"

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
            Assets::EnvAsset* m_env;
            Assets::LightKitAsset* m_lightKit;
            Core::ColorF m_color;
        };

    }

}
