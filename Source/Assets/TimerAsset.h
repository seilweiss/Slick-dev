#pragma once

#include "Core/Asset.h"

#include "hiphop/assets/timer_asset.h"

namespace Slick {

    namespace Assets {

        class TimerAsset : public Asset
        {
            Q_OBJECT

        public:
            TimerAsset(HipHop::Asset asset, SceneFile* sceneFile);

        protected:
            virtual void doSave() override;

        private:
            HipHop::TimerAsset m_timer;
        };

    }

}
