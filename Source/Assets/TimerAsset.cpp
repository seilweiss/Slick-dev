#include "Assets/TimerAsset.h"

namespace Slick {

    namespace Assets {

        TimerAsset::TimerAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_timer(asset)
        {
            setEditor(&m_timer);
        }

        void TimerAsset::inspect(Inspector* inspector)
        {
            BaseAsset::inspect(inspector);

            auto timerGroup = inspector->addGroup("timer");
            auto secondsProp = timerGroup->addNumberInput("time", &m_timer.seconds);
            auto randomRangeProp = timerGroup->addNumberInput("randomRange", &m_timer.randomRange);

            connect(secondsProp, &InspectorProperty::dataChanged, this, &TimerAsset::makeDirty);
            connect(randomRangeProp, &InspectorProperty::dataChanged, this, &TimerAsset::makeDirty);

            inspectLinks(inspector);
        }

    }

}
