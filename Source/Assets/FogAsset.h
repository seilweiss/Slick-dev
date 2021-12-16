#pragma once

#include "Core/Asset.h"
#include "Core/RenderContext.h"

#include "hiphop/assets/fog_asset.h"

namespace Slick {

    namespace Assets {

        class FogAsset : public Asset
        {
            Q_OBJECT

        public:
            FogAsset(HipHop::Asset asset, SceneFile* sceneFile);

            void apply(RenderContext* context);

        protected:
            virtual void doSave() override;

        private:
            HipHop::FogAsset m_fog;
        };

    }

}
