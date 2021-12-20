#pragma once

#include "Core/Asset.h"

#include "hiphop/core/motion_asset.h"

namespace Slick {

    class MotionAsset : public QObject, public Inspectable
    {
        Q_OBJECT

    public:
        MotionAsset(HipHop::MotionAsset& asset, Asset* parent);

        virtual void inspect(Inspector* inspector) override;

    private:
        Asset* m_parent;
        HipHop::MotionAsset& m_motion;
    };

}
