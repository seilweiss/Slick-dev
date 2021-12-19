#pragma once

#include "Core/BaseAsset.h"

#include "hiphop/assets/timer_asset.h"

namespace Slick {

    namespace Assets {

        class TimerAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            TimerAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::TimerAsset m_timer;
        };

    }

}
