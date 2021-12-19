#pragma once

#include "Core/BaseAsset.h"

#include "hiphop/assets/counter_asset.h"

namespace Slick {

    namespace Assets {

        class CounterAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            CounterAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::CounterAsset m_counter;
        };

    }

}
