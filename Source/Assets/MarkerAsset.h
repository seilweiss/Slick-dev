#pragma once

#include "Core/Asset.h"

#include "hiphop/assets/marker_asset.h"

namespace Slick {

    namespace Assets {

        class MarkerAsset : public Asset
        {
            Q_OBJECT

        public:
            MarkerAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::MarkerAsset m_marker;
        };

    }

}
