#include "Assets/SimpleObjectAsset.h"

namespace Slick {

    namespace Assets {

        SimpleObjectAsset::SimpleObjectAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_simpleObj(asset),
            m_collTypeIndex(0)
        {
            setEditor(&m_simpleObj);
        }

        void SimpleObjectAsset::inspect(Inspector* inspector)
        {
            EntAsset::inspect(inspector);

            switch (m_simpleObj.collType)
            {
            case HipHop::SimpleObjAsset::None: m_collTypeIndex = 0; break;
            case HipHop::SimpleObjAsset::Trigger: m_collTypeIndex = 1; break;
            case HipHop::SimpleObjAsset::Static: m_collTypeIndex = 2; break;
            case HipHop::SimpleObjAsset::Dynamic: m_collTypeIndex = 3; break;
            case HipHop::SimpleObjAsset::NPC: m_collTypeIndex = 4; break;
            case HipHop::SimpleObjAsset::Player: m_collTypeIndex = 5; break;
            default: m_collTypeIndex = 0; break;
            }

            auto simpleObjGroup = inspector->addGroup("simpleObject");

            auto animSpeedProp = simpleObjGroup->addNumberInput("animSpeed", &m_simpleObj.animSpeed);
            auto initAnimStateProp = simpleObjGroup->addNumberInput("initialAnimState", &m_simpleObj.initAnimState);
            auto collTypeProp = simpleObjGroup->addComboBox("collisionType", &m_collTypeIndex, { "None", "Trigger", "Static", "Dynamic", "NPC", "Player" });
            auto flagsProp = simpleObjGroup->addNumberInput("flags", &m_simpleObj.flags);

            connect(collTypeProp, &InspectorProperty::dataChanged, this, [=]
            {
                switch (m_collTypeIndex)
                {
                case 0: m_simpleObj.collType = HipHop::SimpleObjAsset::None; break;
                case 1: m_simpleObj.collType = HipHop::SimpleObjAsset::Trigger; break;
                case 2: m_simpleObj.collType = HipHop::SimpleObjAsset::Static; break;
                case 3: m_simpleObj.collType = HipHop::SimpleObjAsset::Dynamic; break;
                case 4: m_simpleObj.collType = HipHop::SimpleObjAsset::NPC; break;
                case 5: m_simpleObj.collType = HipHop::SimpleObjAsset::Player; break;
                default: m_simpleObj.collType = HipHop::SimpleObjAsset::None; break;
                }

                makeDirty();
            });

            connect(animSpeedProp, &InspectorProperty::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(initAnimStateProp, &InspectorProperty::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(flagsProp, &InspectorProperty::dataChanged, this, &SimpleObjectAsset::makeDirty);

            inspectEntity(inspector);
            inspectLinks(inspector);
        }

    }

}
