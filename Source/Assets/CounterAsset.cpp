#include "Assets/CounterAsset.h"

namespace Slick {

    namespace Assets {

        CounterAsset::CounterAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_counter(asset)
        {
            m_counter.Load();

            auto counterGroup = inspector()->addGroup("counter");
            auto countProp = counterGroup->addNumber("count", &m_counter.count);

            connect(countProp, &InspectorProperty::dataChanged, this, &CounterAsset::makeDirty);
        }

        void CounterAsset::doSave()
        {
            m_counter.Save();
        }

    }

}
