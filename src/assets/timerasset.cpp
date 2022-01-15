#include "assets/timerasset.h"

namespace Slick {

    namespace Assets {

        TimerAsset::TimerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_timer(asset)
        {
            setSerializer(&m_timer);
        }

        void TimerAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto timerGroup = root->addGroup("timer", tr("Timer"));
            auto secondsProp = timerGroup->addNumberInput("time", tr("Time"), &m_timer.seconds);
            auto randomRangeProp = timerGroup->addNumberInput("randomRange", tr("Random Range"), &m_timer.randomRange);

            secondsProp->setHelpText(tr("The timer's starting time in seconds."));
            randomRangeProp->setHelpText(tr("On Scene Prepare and Reset, the timer's starting time will be\n"
                                            "offset by a random value between -Random Range and +Random Range.\n"
                                            "(e.g. if Time = 20 and Random Range = 5, the starting time will\n"
                                            "be between 15 and 25."));

            connect(secondsProp, &Inspector::Property::dataChanged, this, &TimerAsset::makeDirty);
            connect(randomRangeProp, &Inspector::Property::dataChanged, this, &TimerAsset::makeDirty);

            inspectLinks(root);
        }

    }

}
