#include "assets/counterasset.h"

namespace Slick {

    namespace Assets {

        CounterAsset::CounterAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_counter(asset)
        {
            setEditor(&m_counter);
        }

        void CounterAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto counterGroup = root->addGroup("counter", tr("Counter"));
            auto countProp = counterGroup->addNumberInput("count", tr("Count"), &m_counter.count);

            countProp->setHelpText(tr("The counter's starting count."));

            connect(countProp, &Inspector::Property::dataChanged, this, &CounterAsset::makeDirty);

            inspectLinks(root);
        }

    }

}
