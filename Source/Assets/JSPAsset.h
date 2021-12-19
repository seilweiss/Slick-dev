#pragma once

#include "Core/Asset.h"
#include "Core/RenderContext.h"
#include "RW/ClumpRenderer.h"

#include "hiphop/assets/jsp_asset.h"

namespace Slick {

    namespace Assets {

        class JSPAsset : public Asset
        {
            Q_OBJECT

        public:
            JSPAsset(HipHop::Asset asset, SceneFile* sceneFile);

            void render(RenderContext* context);

            virtual void setup() override;
            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::JSPAsset m_jsp;
            ClumpRenderer* m_clumpRenderer;
            QList<JSPAsset*> m_jspAssets;
        };

    }

}
