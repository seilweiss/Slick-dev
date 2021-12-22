#pragma once

#include "Core/EntAsset.h"

#include "hiphop/assets/boulder_asset.h"

namespace Slick {

    namespace Assets {

        class BoulderAsset : public EntAsset
        {
            Q_OBJECT

        public:
            BoulderAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::BoulderAsset m_boulder;
        };

    }

}
