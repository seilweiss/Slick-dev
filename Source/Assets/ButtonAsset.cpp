#include "Assets/ButtonAsset.h"

#include "Core/SceneFile.h"

namespace Slick {

    namespace Assets {

        ButtonAsset::ButtonAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_button(asset),
            m_motion(new MotionAsset(m_button.motion, this))
        {
            setEditor(&m_button);
        }

        void ButtonAsset::inspect(Inspector* inspector)
        {
            EntAsset::inspect(inspector);

            auto buttonGroup = inspector->addGroup("button");
            auto pressedModelProp = buttonGroup->addAssetInput("pressedModel", &m_button.modelPressedInfoID, scene());
            auto activateMethodProp = buttonGroup->addComboBox("activateMethod", &m_button.actMethod, { "Button", "Pressure Plate" });
            auto stateProp = buttonGroup->addNumberInput("initialState", &m_button.initButtonState);
            auto resetProp = buttonGroup->addCheckBox("autoReset", &m_button.isReset);
            auto resetDelayProp = buttonGroup->addNumberInput("resetDelay", &m_button.resetDelay);

            auto activateFlagsGroup = buttonGroup->addGroup("activateFlags");

            activateFlagsGroup->setExpanded(false);

            auto sbMeleeProp = activateFlagsGroup->addCheckBox("sbMelee", &m_button.buttonActFlags, HipHop::ButtonAsset::SBMelee);
            auto sbBubbleBounceProp = activateFlagsGroup->addCheckBox("sbBubbleBounce", &m_button.buttonActFlags, HipHop::ButtonAsset::SBBubbleBounce);
            auto sbBubbleBashProp = activateFlagsGroup->addCheckBox("sbBubbleBash", &m_button.buttonActFlags, HipHop::ButtonAsset::SBBubbleBash);
            auto sbBubbleBowlProp = activateFlagsGroup->addCheckBox("sbBubbleBowl", &m_button.buttonActFlags, HipHop::ButtonAsset::SBBubbleBowl);
            auto sbCruiseBubbleProp = activateFlagsGroup->addCheckBox("sbCruiseBubble", &m_button.buttonActFlags, HipHop::ButtonAsset::SBCruiseBubble);
            auto sbBungeeProp = activateFlagsGroup->addCheckBox("sbBungee", &m_button.buttonActFlags, HipHop::ButtonAsset::SBBungee);
            auto patMeleeProp = activateFlagsGroup->addCheckBox("patMelee", &m_button.buttonActFlags, HipHop::ButtonAsset::PatMelee);

            if (sceneFile()->game() >= HipHop::Game::SpongeBobMovie)
            {
                auto patCartwheelProp = activateFlagsGroup->addCheckBox("patCartwheel", &m_button.buttonActFlags, HipHop::ButtonAsset::PatCartwheel);
                patCartwheelProp->setDisplayName("Pat Cartwheel");
                connect(patCartwheelProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            }

            auto patSlamProp = activateFlagsGroup->addCheckBox("patSlam", &m_button.buttonActFlags, HipHop::ButtonAsset::PatSlam);
            auto patThrowNPCProp = activateFlagsGroup->addCheckBox("patThrowNPC", &m_button.buttonActFlags, HipHop::ButtonAsset::PatThrowNPC);
            auto patThrowFruitProp = activateFlagsGroup->addCheckBox("patThrowFruit", &m_button.buttonActFlags, HipHop::ButtonAsset::PatThrowFruit);
            auto sandyMeleeProp = activateFlagsGroup->addCheckBox("sandyMelee", &m_button.buttonActFlags, HipHop::ButtonAsset::SandyMelee);
            auto pressurePlatePlayerProp = activateFlagsGroup->addCheckBox("playerPressurePlate", &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlatePlayer);
            auto pressurePlateNPCProp = activateFlagsGroup->addCheckBox("npcPressurePlate", &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlateNPC);
            auto pressurePlateSBBubbleBowlProp = activateFlagsGroup->addCheckBox("boulderPressurePlate", &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlateSBBubbleBowl);
            auto pressurePlatePatStoneTikiProp = activateFlagsGroup->addCheckBox("stoneTikiPressurePlate", &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlatePatStoneTiki);
            auto pressurePlatePatThrowFruitProp = activateFlagsGroup->addCheckBox("throwFruitPressurePlate", &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlatePatThrowFruit);

            sbMeleeProp->setDisplayName("SB Melee");
            sbBubbleBounceProp->setDisplayName("SB Bubble Bounce");
            sbBubbleBashProp->setDisplayName("SB Bubble Bash");
            sbBubbleBowlProp->setDisplayName("SB Bubble Bowl/Boulder");
            sbCruiseBubbleProp->setDisplayName("SB Cruise Bubble");
            sbBungeeProp->setDisplayName("SB Bungee");
            patMeleeProp->setDisplayName("Pat Melee");
            patSlamProp->setDisplayName("Pat Slam");
            patThrowNPCProp->setDisplayName("Pat Throw NPC");
            patThrowFruitProp->setDisplayName("Pat Throw Fruit");
            sandyMeleeProp->setDisplayName("Sandy Melee");
            pressurePlatePlayerProp->setDisplayName("Player (Pressure Plate)");
            pressurePlateNPCProp->setDisplayName("NPC (Pressure Plate)");
            pressurePlateSBBubbleBowlProp->setDisplayName("Boulder (Pressure Plate)");
            pressurePlatePatStoneTikiProp->setDisplayName("Stone Tiki (Pressure Plate)");
            pressurePlatePatThrowFruitProp->setDisplayName("Throw Fruit (Pressure Plate)");

            connect(pressedModelProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(activateMethodProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(stateProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(resetProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(resetDelayProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(sbMeleeProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(sbBubbleBounceProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(sbBubbleBashProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(sbBubbleBowlProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(sbCruiseBubbleProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(sbBungeeProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(patMeleeProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(patSlamProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(patThrowNPCProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(patThrowFruitProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(sandyMeleeProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(pressurePlatePlayerProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(pressurePlateNPCProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(pressurePlateSBBubbleBowlProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(pressurePlatePatStoneTikiProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
            connect(pressurePlatePatThrowFruitProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);

            m_motion->inspect(inspector);

            inspectEntity(inspector);
            inspectLinks(inspector);
        }

    }

}
