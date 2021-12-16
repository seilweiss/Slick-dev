#pragma once

#include "Core/Asset.h"

#include "hiphop/assets/counter_asset.h"

namespace Slick {

    namespace Assets {

        class CounterAsset : public Asset
        {
            Q_OBJECT

        public:
            CounterAsset(HipHop::Asset asset, SceneFile* sceneFile);

        protected:
            virtual void doSave() override;

        private:
            HipHop::CounterAsset m_counter;
        };

    }

}
