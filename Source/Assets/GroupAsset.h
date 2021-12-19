#pragma once

#include "Core/BaseAsset.h"

#include "hiphop/assets/group_asset.h"

namespace Slick {

    namespace Assets {

        class GroupAsset : public BaseAsset
        {
            Q_OBJECT

        public:
            GroupAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::GroupAsset m_group;
        };

    }

}
