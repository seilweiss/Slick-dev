#include "Assets/SimpleObjectAsset.h"

namespace Slick {

    namespace Assets {

        namespace {

            class CollTypeProxy : public InspectorProxy<int, uint8_t>
            {
            public:
                CollTypeProxy(uint8_t* source) : InspectorProxy(source) {}

                virtual int data() const override
                {
                    switch (*source())
                    {
                    case HipHop::SimpleObjAsset::None: return 0;
                    case HipHop::SimpleObjAsset::Trigger: return 1;
                    case HipHop::SimpleObjAsset::Static: return 2;
                    case HipHop::SimpleObjAsset::Dynamic: return 3;
                    case HipHop::SimpleObjAsset::NPC: return 4;
                    case HipHop::SimpleObjAsset::Player: return 5;
                    default: return -1;
                    }
                }

                virtual void setData(const int& data) const
                {
                    switch (data)
                    {
                    case 0: *source() = HipHop::SimpleObjAsset::None; break;
                    case 1: *source() = HipHop::SimpleObjAsset::Trigger; break;
                    case 2: *source() = HipHop::SimpleObjAsset::Static; break;
                    case 3: *source() = HipHop::SimpleObjAsset::Dynamic; break;
                    case 4: *source() = HipHop::SimpleObjAsset::NPC; break;
                    case 5: *source() = HipHop::SimpleObjAsset::Player; break;
                    default: break;
                    }
                }
            };

        }

        SimpleObjectAsset::SimpleObjectAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_simpleObj(asset)
        {
            setEditor(&m_simpleObj);
        }

        void SimpleObjectAsset::inspect(Inspector* inspector)
        {
            EntAsset::inspect(inspector);

            auto simpleObjGroup = inspector->addGroup("simpleObject", tr("Simple Object"));

            auto animSpeedProp = simpleObjGroup->addNumberInput("animSpeed", tr("Anim Speed"), &m_simpleObj.animSpeed);
            auto initAnimStateProp = simpleObjGroup->addNumberInput("initialAnimState", tr("Initial Anim State"), &m_simpleObj.initAnimState);
            auto collTypeProp = simpleObjGroup->addComboBox("collisionType", tr("Collision Type"), new CollTypeProxy(&m_simpleObj.collType), { tr("None"), tr("Trigger"), tr("Static"), tr("Dynamic"), tr("NPC"), tr("Player") });
            auto flagsProp = simpleObjGroup->addNumberInput("flags", tr("Flags"), &m_simpleObj.flags);

            connect(animSpeedProp, &InspectorProperty::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(initAnimStateProp, &InspectorProperty::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(collTypeProp, &InspectorProperty::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(flagsProp, &InspectorProperty::dataChanged, this, &SimpleObjectAsset::makeDirty);

            inspectEntity(inspector);
            inspectLinks(inspector);
        }

    }

}
