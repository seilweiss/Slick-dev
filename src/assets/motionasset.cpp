#include "assets/motionasset.h"

#include "core/scene.h"

namespace Slick {

    namespace Assets {

        MotionAsset::MotionAsset(HipHop::MotionAsset& asset, Core::Asset* parent) :
            m_parent(parent),
            m_motion(asset)
        {
            Q_ASSERT(parent);
        }

        void MotionAsset::inspect(Inspector::Root* root)
        {
            auto motionGroup = root->addGroup("motion", tr("Motion"));
            auto typeProp = motionGroup->addComboBox("type", tr("Type"), &m_motion.type, { "Extend/Retract", "Orbit", "Spline", "Move Point", "Mechanism", "Pendulum", "None" });
            auto useBankingProp = motionGroup->addCheckBox("useBanking", tr("Use Banking"), &m_motion.use_banking);
            auto stoppedProp = motionGroup->addCheckBox("stopped", tr("Stopped"), &m_motion.flags, HipHop::MotionAsset::Stopped);

            auto erGroup = motionGroup->addGroup("extendRetract", tr("Extend/Retract"));
            auto orbGroup = motionGroup->addGroup("orbit", tr("Orbit"));
            auto splGroup = motionGroup->addGroup("spline", tr("Spline"));
            auto mpGroup = motionGroup->addGroup("movePoint", tr("Move Point"));
            auto mechGroup = motionGroup->addGroup("mechanism", tr("Mechanism"));
            auto penGroup = motionGroup->addGroup("pendulum", tr("Pendulum"));

            erGroup->setExpanded(false);
            orbGroup->setExpanded(false);
            splGroup->setExpanded(false);
            mpGroup->setExpanded(false);
            mechGroup->setExpanded(false);
            penGroup->setExpanded(false);

            typeProp->setHelpText(tr("The motion's type.\n"
                                     "Extend/Retract - Move to one position and back\n"
                                     "Orbit - Move around a center point\n"
                                     "Spline - Move along a Spline asset (not in Scooby/BfBB)\n"
                                     "Move Point - Move along a Move Point path\n"
                                     "Mechanism - Slide, rotate, and scale (scale not in Scooby/BfBB)\n"
                                     "Pendulum - Swing like a pendulum\n"
                                     "None - No movement"));
            stoppedProp->setHelpText(tr("Whether or not the motion is initially stopped.\n"
                                        "If disabled, the entity will start moving on Scene Prepare."));

            auto updateTypeProps = [=]
            {
                erGroup->setVisible(m_motion.type == HipHop::MotionAsset::ExtendRetract);
                orbGroup->setVisible(m_motion.type == HipHop::MotionAsset::Orbit);
                splGroup->setVisible(m_motion.type == HipHop::MotionAsset::Spline);
                mpGroup->setVisible(m_motion.type == HipHop::MotionAsset::MovePoint);
                mechGroup->setVisible(m_motion.type == HipHop::MotionAsset::Mechanism);
                penGroup->setVisible(m_motion.type == HipHop::MotionAsset::Pendulum);
            };

            connect(typeProp, &Inspector::Property::dataChanged, updateTypeProps);
            connect(typeProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
            connect(useBankingProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
            connect(stoppedProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);

            // Extend/Retract
            {
                auto retPosProp = erGroup->addVectorInput("retractPosition", tr("Retract Position"), (Core::Vector3*)&m_motion.er.ret_pos);
                auto extDposProp = erGroup->addVectorInput("extendDistance", tr("Extend Distance"), (Core::Vector3*)&m_motion.er.ext_dpos);
                auto extTmProp = erGroup->addNumberInput("extendTime", tr("Extend Time"), &m_motion.er.ext_tm);
                auto extWaitTmProp = erGroup->addNumberInput("extendWaitTime", tr("Extend Wait Time"), &m_motion.er.ext_wait_tm);
                auto retTmProp = erGroup->addNumberInput("retractTime", tr("Retract Time"), &m_motion.er.ret_tm);
                auto retWaitTmProp = erGroup->addNumberInput("retractWaitTime", tr("Retract Wait Time"), &m_motion.er.ret_wait_tm);

                retPosProp->setHelpText(tr("The motion's starting position."));
                extDposProp->setHelpText(tr("The distance to move."));
                extTmProp->setHelpText(tr("The time it takes to move forward."));
                extWaitTmProp->setHelpText(tr("Optional delay before moving back."));
                retTmProp->setHelpText(tr("The time it takes to move back."));
                retWaitTmProp->setHelpText(tr("Optional delay before moving forward again."));

                connect(retPosProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(extDposProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(extTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(extWaitTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(retTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(retWaitTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
            }

            // Orbit
            {
                auto centerProp = orbGroup->addVectorInput("center", tr("Center"), (Core::Vector3*)&m_motion.orb.center);
                auto wProp = orbGroup->addNumberInput("width", tr("Width"), &m_motion.orb.w);
                auto hProp = orbGroup->addNumberInput("height", tr("Height"), &m_motion.orb.h);
                auto periodProp = orbGroup->addNumberInput("period", tr("Period"), &m_motion.orb.period);

                centerProp->setHelpText(tr("The point to orbit around."));
                wProp->setHelpText(tr("The orbit's X scale."));
                hProp->setHelpText(tr("The orbit's Z scale."));
                periodProp->setHelpText(tr("The time it takes to complete one orbit."));

                connect(centerProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(wProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(hProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(periodProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
            }

            // Spline
            {
                if (m_parent->scene()->game() >= HipHop::Game::SpongeBobMovie)
                {
                    auto splineProp = splGroup->addAssetInput("spline", tr("Spline"), &m_motion.spl.spline_id, m_parent->scene());
                    auto speedProp = splGroup->addNumberInput("speed", tr("Speed"), &m_motion.spl.speed);
                    auto leanModifierProp = splGroup->addNumberInput("leanModifier", tr("Lean Modifier"), &m_motion.spl.lean_modifier);

                    connect(splineProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                    connect(speedProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                    connect(leanModifierProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                }
                else
                {
                    auto unknownProp = splGroup->addNumberInput("unknown", tr("Unknown"), &m_motion.spl.unknown);

                    connect(unknownProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                }
            }

            // Move Point
            {
                auto flagsProp = mpGroup->addNumberInput("flags", tr("Flags"), &m_motion.mp.flags);
                auto mpProp = mpGroup->addAssetInput("movePoint", tr("Move Point"), &m_motion.mp.mp_id, m_parent->scene());
                auto speedProp = mpGroup->addNumberInput("speed", tr("Speed"), &m_motion.mp.speed);

                mpProp->setHelpText(tr("The Move Point to start at."));
                speedProp->setHelpText(tr("The speed to move at in units/sec."));

                connect(flagsProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(mpProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(speedProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
            }

            // Mechanism
            {
                auto typeProp = mechGroup->addComboBox("type", tr("Type"), &m_motion.mech.type, { "Slide", "Rotate", "Slide and Rotate", "Slide then Rotate", "Rotate then Slide" });
                auto returnToStartProp = mechGroup->addCheckBox("returnToStart", tr("Return to Start"), &m_motion.mech.flags, HipHop::MotionMechData::ReturnToStart);
                auto dontLoopProp = mechGroup->addCheckBox("dontLoop", tr("Don't Loop"), &m_motion.mech.flags, HipHop::MotionMechData::DontLoop);
                auto sldAxisProp = mechGroup->addComboBox("slideAxis", tr("Slide Axis"), &m_motion.mech.sld_axis, { "X", "Y", "Z" });
                auto rotAxisProp = mechGroup->addComboBox("rotateAxis", tr("Rotate Axis"), &m_motion.mech.rot_axis, { "X", "Y", "Z" });
                auto scaleAxisProp = mechGroup->addComboBox("scaleAxis", tr("Scale Axis"), &m_motion.mech.scale_axis, { "X", "Y", "Z" });
                auto sldDistProp = mechGroup->addNumberInput("slideDistance", tr("Slide Distance"), &m_motion.mech.sld_dist);
                auto sldTmProp = mechGroup->addNumberInput("slideTime", tr("Slide Time"), &m_motion.mech.sld_tm);
                auto sldAccTmProp = mechGroup->addNumberInput("slideAccelTime", tr("Slide Accel Time"), &m_motion.mech.sld_acc_tm);
                auto sldDecTmProp = mechGroup->addNumberInput("slideDecelTime", tr("Slide Decel Time"), &m_motion.mech.sld_dec_tm);
                auto rotDistProp = mechGroup->addNumberInput("rotateDistance", tr("Rotate Distance"), &m_motion.mech.rot_dist);
                auto rotTmProp = mechGroup->addNumberInput("rotateTime", tr("Rotate Time"), &m_motion.mech.rot_tm);
                auto rotAccTmProp = mechGroup->addNumberInput("rotateAccelTime", tr("Rotate Accel Time"), &m_motion.mech.rot_acc_tm);
                auto rotDecTmProp = mechGroup->addNumberInput("rotateDecelTime", tr("Rotate Decel Time"), &m_motion.mech.rot_dec_tm);
                auto scaleAmountProp = mechGroup->addNumberInput("scaleAmount", tr("Scale Amount"), &m_motion.mech.scale_amount);
                auto scaleDurationProp = mechGroup->addNumberInput("scaleDuration", tr("Scale Duration"), &m_motion.mech.scale_duration);
                auto retDelayProp = mechGroup->addNumberInput("returnDelay", tr("Return Delay"), &m_motion.mech.ret_delay);
                auto postRetDelayProp = mechGroup->addNumberInput("postReturnDelay", tr("Post-Return Delay"), &m_motion.mech.post_ret_delay);

                auto updateMechProps = [=]
                {
                    bool slide = (m_motion.mech.type != HipHop::MotionMechData::Rotate);
                    bool rotate = (m_motion.mech.type != HipHop::MotionMechData::Slide);
                    bool scale = (m_parent->scene()->game() >= HipHop::Game::SpongeBobMovie);

                    sldAxisProp->setVisible(slide);
                    rotAxisProp->setVisible(rotate);
                    scaleAxisProp->setVisible(scale);
                    sldDistProp->setVisible(slide);
                    sldTmProp->setVisible(slide);
                    sldAccTmProp->setVisible(slide);
                    sldDecTmProp->setVisible(slide);
                    rotDistProp->setVisible(rotate);
                    rotTmProp->setVisible(rotate);
                    rotAccTmProp->setVisible(rotate);
                    rotDecTmProp->setVisible(rotate);
                    scaleAmountProp->setVisible(scale);
                    scaleDurationProp->setVisible(scale);
                };

                typeProp->setHelpText(tr("The mechanism's type.\n"
                                         "Slide - slide only, no rotate\n"
                                         "Rotate - rotate only, no slide\n"
                                         "Slide and Rotate - slide and rotate at the same time\n"
                                         "Slide then Rotate - slide first, then rotate\n"
                                         "Rotate then Slide - rotate first, then slide"));
                returnToStartProp->setHelpText(tr("If enabled, the entity will move forward and back in one cycle.\n"
                                                  "If disabled, the entity will only move forward."));
                dontLoopProp->setHelpText(tr("If enabled, the motion will run once, then stop.\n"
                                             "If disabled, the motion will run indefinitely."));
                sldAxisProp->setHelpText(tr("The axis to slide on."));
                rotAxisProp->setHelpText(tr("The axis to rotate on."));
                scaleAxisProp->setHelpText(tr("The axis to scale on."));
                sldDistProp->setHelpText(tr("The distance to slide."));
                sldTmProp->setHelpText(tr("The time it takes to slide."));
                sldAccTmProp->setHelpText(tr("The time it takes to accelerate to full speed.\n"
                                             "This is subtracted from Slide Time in-game."));
                sldDecTmProp->setHelpText(tr("The time it takes to decelerate to rest.\n"
                                             "This is subtracted from Slide Time in-game."));
                rotDistProp->setHelpText(tr("The amount to rotate in degrees."));
                rotTmProp->setHelpText(tr("The time it takes to rotate."));
                rotAccTmProp->setHelpText(tr("The time it takes to accelerate to full speed.\n"
                                             "This is subtracted from Rotate Time in-game."));
                rotDecTmProp->setHelpText(tr("The time it takes to decelerate to rest.\n"
                                             "This is subtracted from Rotate Time in-game."));
                retDelayProp->setHelpText(tr("Optional delay before moving backward."));
                postRetDelayProp->setHelpText(tr("Optional delay before moving forward again."));
                scaleAmountProp->setHelpText(tr("The amount to scale."));
                scaleDurationProp->setHelpText(tr("The time it takes to scale."));

                connect(typeProp, &Inspector::Property::dataChanged, updateMechProps);
                connect(typeProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(returnToStartProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(dontLoopProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(sldAxisProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(rotAxisProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(scaleAxisProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(sldDistProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(sldTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(sldAccTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(sldDecTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(rotDistProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(rotTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(rotAccTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(rotDecTmProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(scaleAmountProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(scaleDurationProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(retDelayProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(postRetDelayProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);

                updateMechProps();
            }

            // Pendulum
            {
                auto flagsProp = penGroup->addNumberInput("flags", tr("Flags"), &m_motion.pen.flags);
                auto planeProp = penGroup->addNumberInput("plane", tr("Plane"), &m_motion.pen.plane);
                auto lenProp = penGroup->addNumberInput("length", tr("Length"), &m_motion.pen.len);
                auto rangeProp = penGroup->addNumberInput("range", tr("Range"), &m_motion.pen.range);
                auto periodProp = penGroup->addNumberInput("period", tr("Period"), &m_motion.pen.period);
                auto phaseProp = penGroup->addNumberInput("phase", tr("Phase"), &m_motion.pen.phase);

                rangeProp->setConvertRadiansToDegrees(true);
                phaseProp->setConvertRadiansToDegrees(true);

                lenProp->setHelpText(tr("The height of the pivot point."));
                rangeProp->setHelpText(tr("The amount in degrees the pendulum swings on each side."));
                periodProp->setHelpText(tr("The time one full swing takes."));
                phaseProp->setHelpText(tr("The start swing offset in degrees."));

                connect(flagsProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(planeProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(lenProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(rangeProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(periodProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
                connect(phaseProp, &Inspector::Property::dataChanged, m_parent, &Core::Asset::makeDirty);
            }

            updateTypeProps();
        }

    }

}
