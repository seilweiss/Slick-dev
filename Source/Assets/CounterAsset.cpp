#include "Assets/CounterAsset.h"

namespace Slick {

    namespace Assets {

        CounterAsset::CounterAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_counter(asset)
        {
            setEditor(&m_counter);
        }

        void CounterAsset::inspect(Inspector* inspector)
        {
            BaseAsset::inspect(inspector);

            auto counterGroup = inspector->addGroup("counter");
            auto countProp = counterGroup->addNumberInput("count", &m_counter.count);

            connect(countProp, &InspectorProperty::dataChanged, this, &CounterAsset::makeDirty);

            inspectLinks(inspector);
        }

    }

}
