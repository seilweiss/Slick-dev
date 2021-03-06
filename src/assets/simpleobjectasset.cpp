#include "assets/simpleobjectasset.h"

namespace Slick {

    namespace Assets {

        namespace {

            class CollTypeProxy : public Inspector::Proxy<int>
            {
            public:
                CollTypeProxy(SimpleObjectAsset* asset) : m_simp(asset->serializer()) {}

                virtual int data() const override
                {
                    switch (m_simp->collType)
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
                    case 0: m_simp->collType = HipHop::SimpleObjAsset::None; break;
                    case 1: m_simp->collType = HipHop::SimpleObjAsset::Trigger; break;
                    case 2: m_simp->collType = HipHop::SimpleObjAsset::Static; break;
                    case 3: m_simp->collType = HipHop::SimpleObjAsset::Dynamic; break;
                    case 4: m_simp->collType = HipHop::SimpleObjAsset::NPC; break;
                    case 5: m_simp->collType = HipHop::SimpleObjAsset::Player; break;
                    default: break;
                    }
                }

            private:
                HipHop::SimpleObjAsset* m_simp;
            };

        }

        SimpleObjectAsset::SimpleObjectAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_simpleObj(asset)
        {
            setSerializer(&m_simpleObj);
        }

        void SimpleObjectAsset::setup()
        {
            EntAsset::setup();
        }

        void SimpleObjectAsset::update()
        {
            EntAsset::update();
        }

        void SimpleObjectAsset::render()
        {
            EntAsset::render();
        }

        void SimpleObjectAsset::inspect(Inspector::Root* root)
        {
            EntAsset::inspect(root);

            auto simpleObjGroup = root->addGroup("simpleObject", tr("Simple Object"));

            auto animSpeedProp = simpleObjGroup->addNumberInput("animSpeed", tr("Anim Speed"), &m_simpleObj.animSpeed);
            auto initAnimStateProp = simpleObjGroup->addNumberInput("initialAnimState", tr("Initial Anim State"), &m_simpleObj.initAnimState);
            auto collTypeProp = simpleObjGroup->addComboBox("collisionType", tr("Collision Type"), new CollTypeProxy(this), { tr("None"), tr("Trigger"), tr("Static"), tr("Dynamic"), tr("NPC"), tr("Player") });
            auto flagsProp = simpleObjGroup->addNumberInput("flags", tr("Flags"), &m_simpleObj.flags);

            connect(animSpeedProp, &Inspector::Property::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(initAnimStateProp, &Inspector::Property::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(collTypeProp, &Inspector::Property::dataChanged, this, &SimpleObjectAsset::makeDirty);
            connect(flagsProp, &Inspector::Property::dataChanged, this, &SimpleObjectAsset::makeDirty);

            inspectEntity(root);
            inspectLinks(root);
        }

        void SimpleObjectManager::setup()
        {
            for (auto asset : assets())
            {
                ((SimpleObjectAsset*)asset)->setup();
            }
        }

        void SimpleObjectManager::update()
        {
            for (auto asset : assets())
            {
                ((SimpleObjectAsset*)asset)->update();
            }
        }

        void SimpleObjectManager::render()
        {
            for (auto asset : assets())
            {
                ((SimpleObjectAsset*)asset)->render();
            }
        }

    }

}
