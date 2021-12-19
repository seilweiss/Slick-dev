#pragma once

#include "Core/BaseAsset.h"
#include "Core/RenderContext.h"

#include "hiphop/assets/fog_asset.h"

namespace Slick {

    namespace Assets {

        class FogAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            FogAsset(HipHop::Asset asset, SceneFile* sceneFile);

            void apply(RenderContext* context);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::FogAsset m_fog;
        };

    }

}
