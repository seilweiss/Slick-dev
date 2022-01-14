#include "assets/triggerasset.h"

namespace Slick {

    namespace Assets {

        namespace {

            inline Core::Vector3 getBoxCenter(HipHop::TriggerAsset* trigger)
            {
                return Core::Vector3((trigger->p[1].x + trigger->p[0].x) / 2.0f,
                                     (trigger->p[1].y + trigger->p[0].y) / 2.0f,
                                     (trigger->p[1].z + trigger->p[0].z) / 2.0f);
            }

            inline Core::Vector3 getBoxSize(HipHop::TriggerAsset* trigger)
            {
                return Core::Vector3(trigger->p[1].x - trigger->p[0].x,
                                     trigger->p[1].y - trigger->p[0].y,
                                     trigger->p[1].z - trigger->p[0].z);
            }

            class CenterOffsetProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                CenterOffsetProxy(HipHop::TriggerAsset* trigger) : Inspector::Proxy<Core::Vector3>(nullptr), m_trigger(trigger) {}

                virtual Core::Vector3 data() const override
                {
                    if (m_trigger->subtype == HipHop::TriggerAsset::Box)
                    {
                        Core::Vector3 center = getBoxCenter(m_trigger);

                        return Core::Vector3(center.x - m_trigger->pos.x,
                                             center.y - m_trigger->pos.y,
                                             center.z - m_trigger->pos.z);
                    }
                    else
                    {
                        return Core::Vector3(m_trigger->p[0].x - m_trigger->pos.x,
                                             m_trigger->p[0].y - m_trigger->pos.y,
                                             m_trigger->p[0].z - m_trigger->pos.z);
                    }
                }

                virtual void setData(const Core::Vector3& offset) const override
                {
                    HipHop::Vec3 center(m_trigger->pos.x + offset.x,
                                        m_trigger->pos.y + offset.y,
                                        m_trigger->pos.z + offset.z);

                    if (m_trigger->subtype == HipHop::TriggerAsset::Box)
                    {
                        Core::Vector3 size = getBoxSize(m_trigger);

                        m_trigger->p[0] = HipHop::Vec3(center.x - size.x / 2.0f,
                                                       center.y - size.y / 2.0f,
                                                       center.z - size.z / 2.0f);

                        m_trigger->p[1] = HipHop::Vec3(center.x + size.x / 2.0f,
                                                       center.y + size.y / 2.0f,
                                                       center.z + size.z / 2.0f);
                    }
                    else
                    {
                        m_trigger->p[0] = center;
                    }
                }

            private:
                HipHop::TriggerAsset* m_trigger;
            };

            class BoxSizeProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                BoxSizeProxy(HipHop::TriggerAsset* trigger) : Inspector::Proxy<Core::Vector3>(nullptr), m_trigger(trigger) {}

                virtual Core::Vector3 data() const override
                {
                    return getBoxSize(m_trigger);
                }

                virtual void setData(const Core::Vector3& size) const override
                {
                    Core::Vector3 center = getBoxCenter(m_trigger);

                    m_trigger->p[0] = HipHop::Vec3(center.x - size.x / 2.0f,
                                                   center.y - size.y / 2.0f,
                                                   center.z - size.z / 2.0f);

                    m_trigger->p[1] = HipHop::Vec3(center.x + size.x / 2.0f,
                                                   center.y + size.y / 2.0f,
                                                   center.z + size.z / 2.0f);
                }

            private:
                HipHop::TriggerAsset* m_trigger;
            };

        }

        TriggerAsset::TriggerAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_trigger(asset)
        {
            setEditor(&m_trigger);
        }

        void TriggerAsset::setup()
        {
            EntAsset::setup();
        }

        void TriggerAsset::update()
        {
            EntAsset::update();
        }

        void TriggerAsset::render()
        {
            EntAsset::render();
        }

        void TriggerAsset::inspect(Inspector::Root* root)
        {
            EntAsset::inspect(root);

            auto triggerGroup = root->addGroup("trigger", tr("Trigger"));
            auto typeProp = triggerGroup->addComboBox("type", tr("Type"), &m_trigger.subtype, { tr("Box"), tr("Sphere"), tr("Cylinder"), tr("Circle") });

            auto centerOffsetProp = triggerGroup->addVectorInput("centerOffset", tr("Center Offset"), new CenterOffsetProxy(&m_trigger));
            auto sizeProp = triggerGroup->addVectorInput("size", tr("Size"), new BoxSizeProxy(&m_trigger));
            auto radiusProp = triggerGroup->addNumberInput("radius", tr("Radius"), &m_trigger.p[1].x);
            auto heightProp = triggerGroup->addNumberInput("height", tr("Height"), &m_trigger.p[1].y);

            auto oneWayProp = triggerGroup->addCheckBox("oneWay", tr("One-Way"), &m_trigger.flags, HipHop::TriggerAsset::OneWay);
            auto oneWayDirectionProp = triggerGroup->addVectorInput("oneWayDirection", tr("One-Way Direction"), (Core::Vector3*)&m_trigger.direction);

            auto updatePropVisibility = [=]
            {
                switch (m_trigger.subtype)
                {
                case HipHop::TriggerAsset::Box:
                    sizeProp->setVisible(true);
                    radiusProp->setVisible(false);
                    heightProp->setVisible(false);
                    break;
                case HipHop::TriggerAsset::Sphere:
                    sizeProp->setVisible(false);
                    radiusProp->setVisible(true);
                    heightProp->setVisible(false);
                    break;
                case HipHop::TriggerAsset::VCylinder:
                    sizeProp->setVisible(false);
                    radiusProp->setVisible(true);
                    heightProp->setVisible(true);
                    break;
                case HipHop::TriggerAsset::VCircle:
                    sizeProp->setVisible(false);
                    radiusProp->setVisible(true);
                    heightProp->setVisible(false);
                    break;
                }
            };

            auto updateOneWayDirectionEnabled = [=]
            {
                oneWayDirectionProp->setEnabled(m_trigger.flags & HipHop::TriggerAsset::OneWay);
            };

            connect(typeProp, &Inspector::Property::dataChanged, updatePropVisibility);
            connect(oneWayProp, &Inspector::Property::dataChanged, updateOneWayDirectionEnabled);

            connect(typeProp, &Inspector::Property::dataChanged, this, &TriggerAsset::makeDirty);
            connect(centerOffsetProp, &Inspector::Property::dataChanged, this, &TriggerAsset::makeDirty);
            connect(sizeProp, &Inspector::Property::dataChanged, this, &TriggerAsset::makeDirty);
            connect(radiusProp, &Inspector::Property::dataChanged, this, &TriggerAsset::makeDirty);
            connect(heightProp, &Inspector::Property::dataChanged, this, &TriggerAsset::makeDirty);
            connect(oneWayProp, &Inspector::Property::dataChanged, this, &TriggerAsset::makeDirty);
            connect(oneWayDirectionProp, &Inspector::Property::dataChanged, this, &TriggerAsset::makeDirty);

            inspectEntity(root);
            inspectLinks(root);

            updatePropVisibility();
            updateOneWayDirectionEnabled();
        }

        void TriggerManager::setup()
        {
            for (auto asset : assets())
            {
                ((TriggerAsset*)asset)->setup();
            }
        }

        void TriggerManager::update()
        {
            for (auto asset : assets())
            {
                ((TriggerAsset*)asset)->update();
            }
        }

        void TriggerManager::render()
        {
            for (auto asset : assets())
            {
                ((TriggerAsset*)asset)->render();
            }
        }

    }

}
