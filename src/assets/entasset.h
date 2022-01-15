#pragma once

#include "assets/baseasset.h"
#include "core/modelinstance.h"

#include "hiphop/core/ent_asset.h"

namespace Slick {

    namespace Assets {

        class LightKitAsset;

        class EntAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            EntAsset(HipHop::Asset asset, Core::SceneFile* sceneFile);

            HipHop::EntAsset* serializer() const { return m_ent; }
            void setSerializer(HipHop::EntAsset* serializer) { BaseAsset::setSerializer(serializer); m_ent = serializer; }

            Core::ModelInstance* model() const { return m_model; }

            Assets::LightKitAsset* lightKit() const { return m_lightKit; }
            void setLightKit(Assets::LightKitAsset* lightKit) { m_lightKit = lightKit; }

            bool renderEnabled() const { return m_renderEnabled; }
            void setRenderEnabled(bool enabled) { m_renderEnabled = enabled; }

            virtual void setup();
            virtual void update();
            virtual void render();

            virtual void inspect(Inspector::Root* root) override;

        protected:
            void inspectEntity(Inspector::Root* root);

        private:
            HipHop::EntAsset m_entDefault;
            HipHop::EntAsset* m_ent;
            Core::ModelInstance* m_model;
            Assets::LightKitAsset* m_lightKit;
            bool m_renderEnabled;
        };

    }

}
