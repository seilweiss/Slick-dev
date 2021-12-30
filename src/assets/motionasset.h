#pragma once

#include "core/asset.h"

#include "hiphop/core/motion_asset.h"

namespace Slick {

    namespace Assets {

        class MotionAsset : public QObject, public Inspector::Object
        {
            Q_OBJECT

        public:
            MotionAsset(HipHop::MotionAsset& asset, Core::Asset* parent);

            virtual void inspect(Inspector::Root* root) override;

        private:
            Core::Asset* m_parent;
            HipHop::MotionAsset& m_motion;
        };

    }

}
