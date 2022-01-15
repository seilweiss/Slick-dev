#include "assets/platformasset.h"

namespace Slick {

    namespace Assets {

        namespace {

            class TypeProxy : public Inspector::Proxy<int>
            {
            public:
                TypeProxy(PlatformAsset* asset) : m_platform(asset->serializer()) {}

                virtual int data() const override
                {
                    return (int)m_platform->type;
                }

                virtual void setData(const int& data) const
                {
                    if (data < 0 || data >= HipHop::PlatformAsset::Count)
                    {
                        return;
                    }

                    m_platform->type = (uint8_t)data;

                    switch (data)
                    {
                    case HipHop::PlatformAsset::ExtendRetract:
                    case HipHop::PlatformAsset::Orbit:
                    case HipHop::PlatformAsset::Spline:
                    case HipHop::PlatformAsset::MovePoint:
                    case HipHop::PlatformAsset::FullyManipulable:
                        m_platform->subtype = HipHop::PlatformAsset::Platform;
                        break;
                    default:
                        m_platform->subtype = (uint8_t)data;
                        break;
                    }
                }

            private:
                HipHop::PlatformAsset* m_platform;
            };

            class OrientListSource : public Inspector::ListSource
            {
            public:
                OrientListSource(PlatformAsset* asset) :
                    m_asset(asset),
                    m_paddle(&asset->serializer()->paddle)
                {
                }

                virtual int size() const override { return m_paddle->countOrient; }
                virtual int max() const override { return sizeof(m_paddle->orient) / sizeof(float); }

                virtual void add()
                {
                    if (m_paddle->countOrient < max())
                    {
                        m_paddle->orient[m_paddle->countOrient++] = 0.0f;
                    }
                }

                virtual void remove(int index)
                {
                    if (m_paddle->countOrient > 0)
                    {
                        while (index < m_paddle->countOrient - 1)
                        {
                            m_paddle->orient[index] = m_paddle->orient[index + 1];
                            index++;
                        }

                        m_paddle->orient[m_paddle->countOrient - 1] = 0;
                        m_paddle->countOrient--;
                    }
                }

                virtual void createGroupItem(Inspector::Group* group, int index) override
                {
                    auto orientProp = group->addNumberInput(&m_paddle->orient[index]);

                    QObject::connect(orientProp, &Inspector::Property::dataChanged, m_asset, &PlatformAsset::makeDirty);
                }

            private:
                PlatformAsset* m_asset;
                HipHop::PlatformPaddleData* m_paddle;
            };

        }

        PlatformAsset::PlatformAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_platform(asset),
            m_motion(new MotionAsset(m_platform.motion, this))
        {
            setSerializer(&m_platform);
        }

        void PlatformAsset::setup()
        {
            EntAsset::setup();
        }

        void PlatformAsset::update()
        {
            EntAsset::update();
        }

        void PlatformAsset::render()
        {
            EntAsset::render();
        }

        void PlatformAsset::inspect(Inspector::Root* root)
        {
            EntAsset::inspect(root);

            auto platformGroup = root->addGroup("platform", tr("Platform"));

            auto typeProp = platformGroup->addComboBox("type", tr("Type"), new TypeProxy(this), {
                                                           tr("Extend/Retract"),
                                                           tr("Orbit"),
                                                           tr("Spline"),
                                                           tr("Move Point"),
                                                           tr("Mechanism"),
                                                           tr("Pendulum"),
                                                           tr("Conveyor Belt"),
                                                           tr("Falling"),
                                                           tr("Forward/Return"),
                                                           tr("Breakaway"),
                                                           tr("Springboard"),
                                                           tr("Teeter-Totter"),
                                                           tr("Paddle"),
                                                           tr("Fully Manipulable")
                                                       });

            auto shakeProp = platformGroup->addCheckBox("shakeOnMount", tr("Shake on Mount"), &m_platform.flags, HipHop::PlatformAsset::Shake);
            auto solidProp = platformGroup->addCheckBox("solid", tr("Solid"), &m_platform.flags, HipHop::PlatformAsset::Solid);

            //auto erGroup = platformGroup->addGroup("extendRetract", tr("Extend/Retract"));
            //auto orbGroup = platformGroup->addGroup("orbit", tr("Orbit"));
            //auto splGroup = platformGroup->addGroup("spline", tr("Spline"));
            //auto mpGroup = platformGroup->addGroup("movePoint", tr("Move Point"));
            //auto mechGroup = platformGroup->addGroup("mechanism", tr("Mechanism"));
            //auto penGroup = platformGroup->addGroup("pendulum", tr("Pendulum"));
            auto cbGroup = platformGroup->addGroup("conveyorBelt", tr("Conveyor Belt"));
            auto fallGroup = platformGroup->addGroup("falling", tr("Falling"));
            auto frGroup = platformGroup->addGroup("forwardReturn", tr("Forward/Return"));
            auto baGroup = platformGroup->addGroup("breakaway", tr("Breakaway"));
            auto sbGroup = platformGroup->addGroup("springboard", tr("Springboard"));
            auto teetGroup = platformGroup->addGroup("teeterTotter", tr("Teeter-Totter"));
            auto paddleGroup = platformGroup->addGroup("paddle", tr("Paddle"));
            //auto fmGroup = platformGroup->addGroup("fullyManipulable", tr("Fully Manipulable"));

            //erGroup->setExpanded(false);
            //orbGroup->setExpanded(false);
            //splGroup->setExpanded(false);
            //mpGroup->setExpanded(false);
            //mechGroup->setExpanded(false);
            //penGroup->setExpanded(false);
            cbGroup->setExpanded(false);
            fallGroup->setExpanded(false);
            frGroup->setExpanded(false);
            baGroup->setExpanded(false);
            sbGroup->setExpanded(false);
            teetGroup->setExpanded(false);
            paddleGroup->setExpanded(false);
            //fmGroup->setExpanded(false);

            auto updateTypeProps = [=]
            {
                //erGroup->setVisible(m_platform.type == HipHop::PlatformAsset::ExtendRetract);
                //orbGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Orbit);
                //splGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Spline);
                //mpGroup->setVisible(m_platform.type == HipHop::PlatformAsset::MovePoint);
                //mechGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Mechanism);
                //penGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Pendulum);
                cbGroup->setVisible(m_platform.type == HipHop::PlatformAsset::ConveyorBelt);
                fallGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Falling);
                frGroup->setVisible(m_platform.type == HipHop::PlatformAsset::ForwardReturn);
                baGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Breakaway);
                sbGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Springboard);
                teetGroup->setVisible(m_platform.type == HipHop::PlatformAsset::TeeterTotter);
                paddleGroup->setVisible(m_platform.type == HipHop::PlatformAsset::Paddle);
                //fmGroup->setVisible(m_platform.type == HipHop::PlatformAsset::FullyManipulable);
            };

            connect(typeProp, &Inspector::Property::dataChanged, [=]
            {
                switch (m_platform.type)
                {
                case HipHop::PlatformAsset::ExtendRetract: m_platform.motion.type = HipHop::MotionAsset::ExtendRetract; break;
                case HipHop::PlatformAsset::Orbit: m_platform.motion.type = HipHop::MotionAsset::Orbit; break;
                case HipHop::PlatformAsset::Spline: m_platform.motion.type = HipHop::MotionAsset::Spline; break;
                case HipHop::PlatformAsset::MovePoint: m_platform.motion.type = HipHop::MotionAsset::MovePoint; break;
                case HipHop::PlatformAsset::Mechanism: m_platform.motion.type = HipHop::MotionAsset::Mechanism; break;
                case HipHop::PlatformAsset::Pendulum: m_platform.motion.type = HipHop::MotionAsset::Pendulum; break;
                default: m_platform.motion.type = HipHop::MotionAsset::None; break;
                }

                root->property("motion.type")->notifyDataChanged();
            });

            connect(typeProp, &Inspector::Property::dataChanged, updateTypeProps);
            connect(typeProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            connect(shakeProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            connect(solidProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);

            // Extend/Retract
            {
            }

            // Orbit
            {
            }

            // Spline
            {
            }

            // Move Point
            {
            }

            // Mechanism
            {
            }

            // Pendulum
            {
            }

            // Conveyor Belt
            {
                auto speedProp = cbGroup->addNumberInput("speed", tr("Speed"), &m_platform.cb.speed);

                connect(speedProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            }

            // Falling
            {
                auto speedProp = fallGroup->addNumberInput("speed", tr("Speed"), &m_platform.fall.speed);
                auto bustModelProp = fallGroup->addAssetInput("bustModel", tr("Bust Model"), &m_platform.fall.bustModelID, scene());

                connect(speedProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(bustModelProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            }

            // Forward/Return
            {
                auto fspeedProp = frGroup->addNumberInput("forwardSpeed", tr("Forward Speed"), &m_platform.fr.fspeed);
                auto rspeedProp = frGroup->addNumberInput("returnSpeed", tr("Return Speed"), &m_platform.fr.rspeed);
                auto retDelayProp = frGroup->addNumberInput("returnDelay", tr("Return Delay"), &m_platform.fr.ret_delay);
                auto postRetDelayProp = frGroup->addNumberInput("postReturnDelay", tr("Post-Return Delay"), &m_platform.fr.post_ret_delay);

                connect(fspeedProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(rspeedProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(retDelayProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(postRetDelayProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            }

            // Breakaway
            {
                auto baDelayProp = baGroup->addNumberInput("breakawayDelay", tr("Breakaway Delay"), &m_platform.ba.ba_delay);
                auto bustModelProp = baGroup->addAssetInput("bustModel", tr("Bust Model"), &m_platform.ba.bustModelID, scene());
                auto resetDelayProp = baGroup->addNumberInput("resetDelay", tr("Reset Delay"), &m_platform.ba.reset_delay);
                auto allowSneakProp = baGroup->addCheckBox("allowSneak", tr("Allow Sneak"), &m_platform.ba.breakflags, HipHop::PlatformBreakawayData::AllowSneak);

                connect(baDelayProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(bustModelProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(resetDelayProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(allowSneakProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            }

            // Springboard
            {
                auto jmph1Prop = sbGroup->addNumberInput("height1", tr("Height 1"), &m_platform.sb.jmph[0]);
                auto jmph2Prop = sbGroup->addNumberInput("height2", tr("Height 2"), &m_platform.sb.jmph[1]);
                auto jmph3Prop = sbGroup->addNumberInput("height3", tr("Height 3"), &m_platform.sb.jmph[2]);
                auto jmpbounceProp = sbGroup->addNumberInput("heightBubbleBounce", tr("Height (Bubble Bounce)"), &m_platform.sb.jmpbounce);
                auto anim1Prop = sbGroup->addAssetInput("anim1", tr("Anim 1"), &m_platform.sb.animID[0], scene());
                auto anim2Prop = sbGroup->addAssetInput("anim2", tr("Anim 2"), &m_platform.sb.animID[1], scene());
                auto anim3Prop = sbGroup->addAssetInput("anim3", tr("Anim 3"), &m_platform.sb.animID[2], scene());
                auto jmpdirProp = sbGroup->addVectorInput("direction", tr("Direction"), (Core::Vector3*)&m_platform.sb.jmpdir);
                auto lockViewProp = sbGroup->addCheckBox("lockView", tr("Lock View"), &m_platform.sb.springflags, HipHop::PlatformSpringboardData::LockView);
                auto lockMovementProp = sbGroup->addCheckBox("lockMovement", tr("Lock Movement"), &m_platform.sb.springflags, HipHop::PlatformSpringboardData::LockMovement);

                connect(jmph1Prop, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(jmph2Prop, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(jmph3Prop, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(jmpbounceProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(anim1Prop, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(anim2Prop, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(anim3Prop, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(jmpdirProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(lockViewProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(lockMovementProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            }

            // Teeter-Totter
            {
                auto itiltProp = teetGroup->addNumberInput("initialTilt", tr("Initial Tilt"), &m_platform.teet.itilt);
                auto maxtiltProp = teetGroup->addNumberInput("maxTilt", tr("Max Tilt"), &m_platform.teet.maxtilt);
                auto invmassProp = teetGroup->addNumberInput("inverseMass", tr("Inverse Mass"), &m_platform.teet.invmass);

                itiltProp->setConvertRadiansToDegrees(true);
                maxtiltProp->setConvertRadiansToDegrees(true);

                connect(itiltProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(maxtiltProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(invmassProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            }

            // Paddle
            {
                auto startOrientProp = paddleGroup->addNumberInput("startOrient", tr("Start Orient"), &m_platform.paddle.startOrient);
                auto orientsGroup = paddleGroup->addGroup("orients", tr("Orients"));
                auto orientLoopProp = paddleGroup->addNumberInput("orientLoop", tr("Orient Loop"), &m_platform.paddle.orientLoop);
                auto paddleFlagsProp = paddleGroup->addNumberInput("flags", tr("Flags"), &m_platform.paddle.paddleFlags);
                auto rotateSpeedProp = paddleGroup->addNumberInput("rotateSpeed", tr("Rotate Speed"), &m_platform.paddle.rotateSpeed);
                auto accelTimeProp = paddleGroup->addNumberInput("accelTime", tr("Accel Time"), &m_platform.paddle.accelTime);
                auto decelTimeProp = paddleGroup->addNumberInput("decelTime", tr("Decel Time"), &m_platform.paddle.decelTime);
                auto hubRadiusProp = paddleGroup->addNumberInput("hubRadius", tr("Hub Radius"), &m_platform.paddle.hubRadius);

                orientsGroup->setListSource(new OrientListSource(this));

                auto updateStartOrient = [=]
                {
                    startOrientProp->setMinimum(0);
                    startOrientProp->setMaximum(m_platform.paddle.countOrient - 1);
                    startOrientProp->requestRefresh();
                };

                updateStartOrient();

                connect(startOrientProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);

                connect(orientsGroup, &Inspector::Group::listItemAdded, updateStartOrient);
                connect(orientsGroup, &Inspector::Group::listItemRemoved, updateStartOrient);
                connect(orientsGroup, &Inspector::Group::listItemAdded, this, &PlatformAsset::makeDirty);
                connect(orientsGroup, &Inspector::Group::listItemRemoved, this, &PlatformAsset::makeDirty);

                connect(orientLoopProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(paddleFlagsProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(rotateSpeedProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(accelTimeProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(decelTimeProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
                connect(hubRadiusProp, &Inspector::Property::dataChanged, this, &PlatformAsset::makeDirty);
            }

            // Fully Manipulable
            {
            }

            m_motion->inspect(root);

            inspectEntity(root);
            inspectLinks(root);

            updateTypeProps();
        }

        void PlatformManager::setup()
        {
            for (auto asset : assets())
            {
                ((PlatformAsset*)asset)->setup();
            }
        }

        void PlatformManager::update()
        {
            for (auto asset : assets())
            {
                ((PlatformAsset*)asset)->update();
            }
        }

        void PlatformManager::render()
        {
            for (auto asset : assets())
            {
                ((PlatformAsset*)asset)->render();
            }
        }

    }

}
