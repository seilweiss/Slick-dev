#pragma once

#include "Core/EntAsset.h"

#include "hiphop/assets/anim_list_asset.h"

namespace Slick {

    namespace Assets {

        class AnimListAsset : public Asset
        {
            Q_OBJECT

        public:
            AnimListAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::AnimListAsset m_animList;
        };

    }

}
