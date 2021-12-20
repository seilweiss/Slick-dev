#pragma once

#include "Core/EntAsset.h"
#include "Core/MotionAsset.h"

#include "hiphop/assets/button_asset.h"

namespace Slick {

    namespace Assets {

        class ButtonAsset : public EntAsset
        {
            Q_OBJECT

        public:
            ButtonAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::ButtonAsset m_button;
            MotionAsset* m_motion;
        };

    }

}
