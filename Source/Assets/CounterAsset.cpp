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

            auto counterGroup = inspector->addGroup("counter", tr("Counter"));
            auto countProp = counterGroup->addNumberInput("count", tr("Count"), &m_counter.count);

            countProp->setHelpText(tr("The counter's starting count."));

            connect(countProp, &InspectorProperty::dataChanged, this, &CounterAsset::makeDirty);

            inspectLinks(inspector);
        }

    }

}
