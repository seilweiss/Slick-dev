#pragma once

#include "Core/EntAsset.h"

#include "hiphop/assets/simple_obj_asset.h"

namespace Slick {

    namespace Assets {

        class SimpleObjectAsset : public EntAsset
        {
            Q_OBJECT

        public:
            SimpleObjectAsset(HipHop::Asset asset, SceneFile* sceneFile);

            virtual void inspect(Inspector* inspector) override;

        private:
            HipHop::SimpleObjAsset m_simpleObj;
        };

    }

}
