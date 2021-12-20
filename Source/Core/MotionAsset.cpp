#include "Core/MotionAsset.h"

#include "Core/SceneFile.h"

namespace Slick {

    MotionAsset::MotionAsset(HipHop::MotionAsset& asset, Asset* parent) :
        m_parent(parent),
        m_motion(asset)
    {
        Q_ASSERT(parent);
    }

    void MotionAsset::inspect(Inspector* inspector)
    {
        auto motionGroup = inspector->addGroup("motion");
        auto typeProp = motionGroup->addComboBox("type", &m_motion.type, { "Extend/Retract", "Orbit", "Spline", "Move Point", "Mechanism", "Pendulum", "None" });
        auto useBankingProp = motionGroup->addCheckBox("useBanking", &m_motion.use_banking);
        auto stoppedProp = motionGroup->addCheckBox("stopped", &m_motion.flags, HipHop::MotionAsset::Stopped);

        auto erGroup = motionGroup->addGroup("extendRetract");
        auto orbGroup = motionGroup->addGroup("orbit");
        auto splGroup = motionGroup->addGroup("spline");
        auto mpGroup = motionGroup->addGroup("movePoint");
        auto mechGroup = motionGroup->addGroup("mechanism");
        auto penGroup = motionGroup->addGroup("pendulum");

        erGroup->setExpanded(false);
        orbGroup->setExpanded(false);
        splGroup->setExpanded(false);
        mpGroup->setExpanded(false);
        mechGroup->setExpanded(false);
        penGroup->setExpanded(false);

        auto updateTypeProps = [=]
        {
            erGroup->setVisible(m_motion.type == HipHop::MotionAsset::ExtendRetract);
            orbGroup->setVisible(m_motion.type == HipHop::MotionAsset::Orbit);
            splGroup->setVisible(m_motion.type == HipHop::MotionAsset::Spline);
            mpGroup->setVisible(m_motion.type == HipHop::MotionAsset::MovePoint);
            mechGroup->setVisible(m_motion.type == HipHop::MotionAsset::Mechanism);
            penGroup->setVisible(m_motion.type == HipHop::MotionAsset::Pendulum);
        };

        connect(typeProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
        connect(typeProp, &InspectorProperty::dataChanged, updateTypeProps);
        connect(useBankingProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
        connect(stoppedProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);

        // Extend/Retract
        {
            auto retPosProp = erGroup->addVectorInput("retractPosition", (Vector3*)&m_motion.er.ret_pos);
            auto extDposProp = erGroup->addVectorInput("extendDistance", (Vector3*)&m_motion.er.ext_dpos);
            auto extTmProp = erGroup->addNumberInput("extendTime", &m_motion.er.ext_tm);
            auto extWaitTmProp = erGroup->addNumberInput("extendWaitTime", &m_motion.er.ext_wait_tm);
            auto retTmProp = erGroup->addNumberInput("retractTime", &m_motion.er.ret_tm);
            auto retWaitTmProp = erGroup->addNumberInput("retractWaitTime", &m_motion.er.ret_wait_tm);

            erGroup->setDisplayName("Extend/Retract");

            connect(retPosProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(extDposProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(extTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(extWaitTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(retTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(retWaitTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
        }

        // Orbit
        {
            auto centerProp = orbGroup->addVectorInput("center", (Vector3*)&m_motion.orb.center);
            auto wProp = orbGroup->addNumberInput("width", &m_motion.orb.w);
            auto hProp = orbGroup->addNumberInput("height", &m_motion.orb.h);
            auto periodProp = orbGroup->addNumberInput("period", &m_motion.orb.period);

            connect(centerProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(wProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(hProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(periodProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
        }

        // Spline
        {
            if (m_parent->sceneFile()->game() >= HipHop::Game::SpongeBobMovie)
            {
                auto splineProp = splGroup->addAssetInput("spline", &m_motion.spl.spline_id, m_parent->scene());
                auto speedProp = splGroup->addNumberInput("speed", &m_motion.spl.speed);
                auto leanModifierProp = splGroup->addNumberInput("leanModifier", &m_motion.spl.lean_modifier);

                connect(splineProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
                connect(speedProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
                connect(leanModifierProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            }
            else
            {
                auto unknownProp = splGroup->addNumberInput("unknown", &m_motion.spl.unknown);

                connect(unknownProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            }
        }

        // Move Point
        {
            auto flagsProp = mpGroup->addNumberInput("flags", &m_motion.mp.flags);
            auto mpProp = mpGroup->addAssetInput("movePoint", &m_motion.mp.mp_id, m_parent->scene());
            auto speedProp = mpGroup->addNumberInput("speed", &m_motion.mp.speed);

            connect(flagsProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(mpProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(speedProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
        }

        // Mechanism
        {
            auto typeProp = mechGroup->addComboBox("type", &m_motion.mech.type, { "Slide", "Rotate", "Slide and Rotate", "Slide then Rotate", "Rotate then Slide" });
            auto returnToStartProp = mechGroup->addCheckBox("returnToStart", &m_motion.mech.flags, HipHop::MotionMechData::ReturnToStart);
            auto dontLoopProp = mechGroup->addCheckBox("dontLoop", &m_motion.mech.flags, HipHop::MotionMechData::DontLoop);
            auto sldAxisProp = mechGroup->addComboBox("slideAxis", &m_motion.mech.sld_axis, { "X", "Y", "Z" });
            auto rotAxisProp = mechGroup->addComboBox("rotateAxis", &m_motion.mech.rot_axis, { "X", "Y", "Z" });
            auto scaleAxisProp = mechGroup->addComboBox("scaleAxis", &m_motion.mech.scale_axis, { "X", "Y", "Z" });
            auto sldDistProp = mechGroup->addNumberInput("slideDistance", &m_motion.mech.sld_dist);
            auto sldTmProp = mechGroup->addNumberInput("slideTime", &m_motion.mech.sld_tm);
            auto sldAccTmProp = mechGroup->addNumberInput("slideAccelTime", &m_motion.mech.sld_acc_tm);
            auto sldDecTmProp = mechGroup->addNumberInput("slideDecelTime", &m_motion.mech.sld_dec_tm);
            auto rotDistProp = mechGroup->addNumberInput("rotateDistance", &m_motion.mech.rot_dist);
            auto rotTmProp = mechGroup->addNumberInput("rotateTime", &m_motion.mech.rot_tm);
            auto rotAccTmProp = mechGroup->addNumberInput("rotateAccelTime", &m_motion.mech.rot_acc_tm);
            auto rotDecTmProp = mechGroup->addNumberInput("rotateDecelTime", &m_motion.mech.rot_dec_tm);
            auto retDelayProp = mechGroup->addNumberInput("returnDelay", &m_motion.mech.ret_delay);
            auto postRetDelayProp = mechGroup->addNumberInput("postReturnDelay", &m_motion.mech.post_ret_delay);
            auto scaleAmountProp = mechGroup->addNumberInput("scaleAmount", &m_motion.mech.scale_amount);
            auto scaleDurationProp = mechGroup->addNumberInput("scaleDuration", &m_motion.mech.scale_duration);

            dontLoopProp->setDisplayName("Don't Loop");
            postRetDelayProp->setDisplayName("Post-Return Delay");

            auto updateMechProps = [=]
            {
                bool slide = (m_motion.mech.type != HipHop::MotionMechData::Rotate);
                bool rotate = (m_motion.mech.type != HipHop::MotionMechData::Slide);
                bool scale = (m_parent->sceneFile()->game() >= HipHop::Game::SpongeBobMovie);

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

            connect(typeProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(typeProp, &InspectorProperty::dataChanged, updateMechProps);
            connect(returnToStartProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(dontLoopProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(sldAxisProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(rotAxisProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(scaleAxisProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(sldDistProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(sldTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(sldAccTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(sldDecTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(rotDistProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(rotTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(rotAccTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(rotDecTmProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(retDelayProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(postRetDelayProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(scaleAmountProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(scaleDurationProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);

            updateMechProps();
        }

        // Pendulum
        {
            auto flagsProp = penGroup->addNumberInput("flags", &m_motion.pen.flags);
            auto planeProp = penGroup->addNumberInput("plane", &m_motion.pen.plane);
            auto lenProp = penGroup->addNumberInput("length", &m_motion.pen.len);
            auto rangeProp = penGroup->addNumberInput("range", &m_motion.pen.range);
            auto periodProp = penGroup->addNumberInput("period", &m_motion.pen.period);
            auto phaseProp = penGroup->addNumberInput("phase", &m_motion.pen.phase);

            connect(flagsProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(planeProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(lenProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(rangeProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(periodProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
            connect(phaseProp, &InspectorProperty::dataChanged, m_parent, &Asset::makeDirty);
        }

        updateTypeProps();
    }

}
