#include "Assets/TimerAsset.h"

namespace Slick {

    namespace Assets {

        TimerAsset::TimerAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_timer(asset)
        {
            m_timer.Load();

            auto timerGroup = inspector()->addGroup("timer");
            auto secondsProp = timerGroup->addNumber("time", &m_timer.seconds);
            auto randomRangeProp = timerGroup->addNumber("randomRange", &m_timer.randomRange);

            connect(secondsProp, &InspectorProperty::dataChanged, this, &TimerAsset::makeDirty);
            connect(randomRangeProp, &InspectorProperty::dataChanged, this, &TimerAsset::makeDirty);
        }

        void TimerAsset::doSave()
        {
            m_timer.Save();
        }

    }

}
