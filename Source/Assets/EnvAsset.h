#pragma once

#include "Core/BaseAsset.h"
#include "Core/RenderContext.h"

#include "hiphop/assets/env_asset.h"

namespace Slick {

    namespace Assets {

        class JSPAsset;
        class LightKitAsset;

        class EnvAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            EnvAsset(HipHop::Asset asset, SceneFile* sceneFile);

            LightKitAsset* objectLightKit() const { return m_objLightKit; }

            void render(RenderContext* context);

            virtual void setup() override;
            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::EnvAsset m_env;
            JSPAsset* m_jspInfo;
            LightKitAsset* m_objLightKit;
        };

    }

}
