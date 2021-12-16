#pragma once

#include "Core/Asset.h"
#include "Core/RenderContext.h"

#include "hiphop/assets/env_asset.h"

namespace Slick {

    namespace Assets {

        class JSPAsset;

        class EnvAsset : public Asset
        {
            Q_OBJECT

        public:
            EnvAsset(HipHop::Asset asset, SceneFile* sceneFile);

            void render(RenderContext* context);

        protected:
            virtual void doSave() override;

        private:
            HipHop::EnvAsset m_env;
            bool m_setup;
            JSPAsset* m_jspInfo;

            void setup();
        };

    }

}
