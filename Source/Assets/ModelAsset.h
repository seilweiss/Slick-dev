#pragma once

#include "Core/Asset.h"
#include "Core/RenderContext.h"
#include "RW/ClumpRenderer.h"

#include "hiphop/assets/model_asset.h"

namespace Slick {

    namespace Assets {

        class ModelAsset : public Asset
        {
            Q_OBJECT

        public:
            ModelAsset(HipHop::Asset asset, SceneFile* sceneFile);

            ClumpRenderer* renderer() const { return m_clumpRenderer; }

            void render(RenderContext* context);

            virtual void setup() override;
            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::ModelAsset m_model;
            ClumpRenderer* m_clumpRenderer;
        };

    }

}
