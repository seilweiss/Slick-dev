#include "Assets/ButtonAsset.h"

#include "Core/Scene.h"

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

            bool bfbb = (scene()->game() == HipHop::Game::BattleForBikiniBottom);

            auto buttonGroup = inspector->addGroup("button", tr("Button"));
            auto pressedModelProp = buttonGroup->addAssetInput("pressedModel", tr("Pressed Model"), &m_button.modelPressedInfoID, scene());
            auto activateMethodProp = buttonGroup->addComboBox("activateMethod", tr("Activate Method"), &m_button.actMethod, { tr("Button"), tr("Pressure Plate") });
            auto stateProp = buttonGroup->addNumberInput("initialState", tr("Initial State"), &m_button.initButtonState);
            auto resetProp = buttonGroup->addCheckBox("autoReset", tr("Auto Reset"), &m_button.isReset);
            auto resetDelayProp = buttonGroup->addNumberInput("resetDelay", tr("Reset Delay"), &m_button.resetDelay);

            auto activateFlagsGroup = buttonGroup->addGroup("activateFlags", tr("Activate Flags"));

            activateFlagsGroup->setExpanded(false);

            auto sbMeleeProp = activateFlagsGroup->addCheckBox("sbMelee", bfbb ? tr("SB Bubble Spin") : tr("SB Karate Spin"), &m_button.buttonActFlags, HipHop::ButtonAsset::SBMelee);
            auto sbBubbleBounceProp = activateFlagsGroup->addCheckBox("sbBubbleBounce", tr("SB Bubble Bounce"), &m_button.buttonActFlags, HipHop::ButtonAsset::SBBubbleBounce);
            auto sbBubbleBashProp = activateFlagsGroup->addCheckBox("sbBubbleBash", bfbb ? tr("SB Bubble Bash") : tr("SB Bash"), &m_button.buttonActFlags, HipHop::ButtonAsset::SBBubbleBash);
            auto sbBubbleBowlProp = activateFlagsGroup->addCheckBox("sbBubbleBowl", bfbb ? tr("SB Bubble Bowl/Boulder") : tr("SB SpongeBowl/Boulder"), &m_button.buttonActFlags, HipHop::ButtonAsset::SBBubbleBowl);
            auto sbCruiseBubbleProp = activateFlagsGroup->addCheckBox("sbCruiseBubble", bfbb ? tr("SB Cruise Bubble") : tr("SB Sonic Wave Guitar"), &m_button.buttonActFlags, HipHop::ButtonAsset::SBCruiseBubble);
            auto sbBungeeProp = activateFlagsGroup->addCheckBox("sbBungee", tr("SB Bungee"), &m_button.buttonActFlags, HipHop::ButtonAsset::SBBungee);
            auto patMeleeProp = activateFlagsGroup->addCheckBox("patMelee", bfbb ? tr("Pat Melee") : tr("Pat Star Spin"), &m_button.buttonActFlags, HipHop::ButtonAsset::PatMelee);
            auto patCartwheelProp = activateFlagsGroup->addCheckBox("patCartwheel", tr("Pat Cartwheel"), &m_button.buttonActFlags, HipHop::ButtonAsset::PatCartwheel);
            auto patSlamProp = activateFlagsGroup->addCheckBox("patSlam", tr("Pat Slam"), &m_button.buttonActFlags, HipHop::ButtonAsset::PatSlam);
            auto patThrowNPCProp = activateFlagsGroup->addCheckBox("patThrowNPC", tr("Pat Throw NPC"), &m_button.buttonActFlags, HipHop::ButtonAsset::PatThrowNPC);
            auto patThrowFruitProp = activateFlagsGroup->addCheckBox("patThrowFruit", tr("Pat Throw Fruit"), &m_button.buttonActFlags, HipHop::ButtonAsset::PatThrowFruit);
            auto sandyMeleeProp = activateFlagsGroup->addCheckBox("sandyMelee", tr("Sandy Melee"), &m_button.buttonActFlags, HipHop::ButtonAsset::SandyMelee);
            auto pressurePlatePlayerProp = activateFlagsGroup->addCheckBox("playerPressurePlate", tr("Player (Pressure Plate)"), &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlatePlayer);
            auto pressurePlateNPCProp = activateFlagsGroup->addCheckBox("npcPressurePlate", tr("NPC (Pressure Plate)"), &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlateNPC);
            auto pressurePlateSBBubbleBowlProp = activateFlagsGroup->addCheckBox("boulderPressurePlate", tr("Boulder (Pressure Plate)"), &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlateSBBubbleBowl);
            auto pressurePlatePatStoneTikiProp = activateFlagsGroup->addCheckBox("stoneTikiPressurePlate", tr("Stone Tiki (Pressure Plate)"), &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlatePatStoneTiki);
            auto pressurePlatePatThrowFruitProp = activateFlagsGroup->addCheckBox("throwFruitPressurePlate", tr("Throw Fruit (Pressure Plate)"), &m_button.buttonActFlags, HipHop::ButtonAsset::PressurePlatePatThrowFruit);

            patCartwheelProp->setVisible(!bfbb);

            pressedModelProp->setHelpText(tr("Model to render when the button is pressed.\n"
                                             "Default is the button's normal model (in Entity)."));
            activateMethodProp->setHelpText(tr("The button's activation method.\n\n"
                                               "Button - Stays pressed upon being hit, and has a flashing effect.\n"
                                               "Pressure Plate - Automatically unpresses when no longer being hit."));
            stateProp->setHelpText(tr("The button's initial state."));
            resetProp->setHelpText(tr("If enabled, the button will automatically unpress after Reset Delay."));
            resetDelayProp->setHelpText(tr("If Auto Reset is enabled, the button will automatically unpress after this delay."));
            sbMeleeProp->setHelpText(bfbb ? tr("Button can be pressed with SpongeBob's Bubble Spin.") :
                                            tr("Button can be pressed with SpongeBob's Karate Spin."));
            sbBubbleBounceProp->setHelpText(tr("Button can be pressed with SpongeBob's Bubble Bounce."));
            sbBubbleBashProp->setHelpText(bfbb ? tr("Button can be pressed with SpongeBob's Bubble Bash.") :
                                                 tr("Button can be pressed with SpongeBob's Bash."));
            sbBubbleBowlProp->setHelpText(bfbb ? tr("Button can be pressed with SpongeBob's Bubble Bowl or any Boulder.") :
                                                 tr("Button can be pressed with SpongeBob's SpongeBowl or any Boulder."));
            sbCruiseBubbleProp->setHelpText(bfbb ? tr("Button can be pressed with SpongeBob's Cruise Bubble.") :
                                                   tr("Button can be pressed with SpongeBob's Sonic Wave Guitar."));
            sbBungeeProp->setHelpText(tr("Button can be pressed by SpongeBob while on a Bungee Hook."));
            patMeleeProp->setHelpText(bfbb ? tr("Button can be pressed with Patrick's Belly Bounce.") :
                                             tr("Button can be pressed with Patrick's Star Spin."));
            patCartwheelProp->setHelpText(tr("Button can be pressed with Patrick's Cartwheel."));
            patSlamProp->setHelpText(tr("Button can be pressed with Patrick's Slam."));
            patThrowNPCProp->setHelpText(tr("Button can be pressed with a thrown NPC."));
            patThrowFruitProp->setHelpText(tr("Button can be pressed with a Throw Fruit."));
            sandyMeleeProp->setHelpText(tr("Button can be pressed with Sandy's melee."));
            pressurePlatePlayerProp->setHelpText(tr("Pressure Plate can be pressed by the player."));
            pressurePlateNPCProp->setHelpText(tr("Pressure Plate can be pressed by NPCs."));
            pressurePlateSBBubbleBowlProp->setHelpText(bfbb ? tr("Pressure Plate can be pressed by SpongeBob's Bubble Bowl or any Boulder.") :
                                                              tr("Pressure Plate can be pressed by SpongeBob's SpongeBowl or any Boulder."));
            pressurePlatePatStoneTikiProp->setHelpText(tr("Pressure Plate can be pressed with a Stone Tiki."));
            pressurePlatePatThrowFruitProp->setHelpText(tr("Pressure Plate can be pressed with a Throw Fruit."));

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
            connect(patCartwheelProp, &InspectorProperty::dataChanged, this, &ButtonAsset::makeDirty);
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
