#pragma once

#include "Core/BaseAsset.h"
#include "Core/RenderContext.h"

#include "hiphop/assets/env_asset.h"

namespace Slick {

    namespace Assets {

        class JSPAsset;

        class EnvAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            EnvAsset(HipHop::Asset asset, SceneFile* sceneFile);

            void render(RenderContext* context);

            virtual void setup() override;
            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::EnvAsset m_env;
            JSPAsset* m_jspInfo;
        };

    }

}
