#include "assets/boulderasset.h"

#include "core/scene.h"

#include <glm/glm.hpp>

namespace Slick {

    namespace Assets {

        BoulderAsset::BoulderAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_boulder(asset)
        {
            setSerializer(&m_boulder);
        }

        void BoulderAsset::setup()
        {
            EntAsset::setup();
        }

        void BoulderAsset::update()
        {
            EntAsset::update();
        }

        void BoulderAsset::render()
        {
            EntAsset::render();
        }

        void BoulderAsset::inspect(Inspector::Root* root)
        {
            EntAsset::inspect(root);

            auto boulderGroup = root->addGroup("boulder", tr("Boulder"));
            auto gravityProp = boulderGroup->addNumberInput("gravity", tr("Gravity"), &m_boulder.gravity);
            auto massProp = boulderGroup->addNumberInput("mass", tr("Mass"), &m_boulder.mass);
            auto bounceProp = boulderGroup->addNumberInput("bounce", tr("Bounce"), &m_boulder.bounce);
            auto frictionProp = boulderGroup->addNumberInput("friction", tr("Friction"), &m_boulder.friction);
            auto statFricProp = boulderGroup->addNumberInput("staticFriction", tr("Static Friction"), &m_boulder.statFric);
            auto maxVelProp = boulderGroup->addNumberInput("maxVelocity", tr("Max Velocity"), &m_boulder.maxVel);
            auto maxAngVelProp = boulderGroup->addNumberInput("maxAngularVelocity", tr("Max Angular Velocity"), &m_boulder.maxAngVel);
            auto stickinessProp = boulderGroup->addNumberInput("stickiness", tr("Stickiness"), &m_boulder.stickiness);
            auto bounceDampProp = boulderGroup->addNumberInput("bounceDamp", tr("Bounce Damp"), &m_boulder.bounceDamp);
            auto killTimerProp = boulderGroup->addNumberInput("killTimer", tr("Kill Timer"), &m_boulder.killtimer);
            auto hitpointsProp = boulderGroup->addNumberInput("hitPoints", tr("Hit Points"), &m_boulder.hitpoints);
            auto soundIDProp = boulderGroup->addAssetInput("sound", tr("Sound"), &m_boulder.soundID, scene());
            auto volumeProp = boulderGroup->addNumberInput("volume", tr("Volume"), &m_boulder.volume);
            auto minSoundVelProp = boulderGroup->addNumberInput("minSoundVelocity", tr("Min Sound Velocity"), &m_boulder.minSoundVel);
            auto maxSoundVelProp = boulderGroup->addNumberInput("maxSoundVelocity", tr("Max Sound Velocity"), &m_boulder.maxSoundVel);
            auto innerRadiusProp = boulderGroup->addNumberInput("innerRadius", tr("Inner Radius"), &m_boulder.innerRadius);
            auto outerRadiusProp = boulderGroup->addNumberInput("outerRadius", tr("Outer Radius"), &m_boulder.outerRadius);
            auto sphereRadiusProp = boulderGroup->addNumberInput("sphereRadius", tr("Sphere Radius"), &m_boulder.fSphereRadius);
            auto boneIndexProp = boulderGroup->addNumberInput("boneIndex", tr("Bone Index"), &m_boulder.uBoneIndex);

            auto boulderFlagsGroup = boulderGroup->addGroup("flags", tr("Flags"));
            auto canHitWallsProp = boulderFlagsGroup->addCheckBox("canHitWalls", tr("Can Hit Walls"), &m_boulder.flags, HipHop::BoulderAsset::CanHitWalls);
            auto damagePlayerProp = boulderFlagsGroup->addCheckBox("damagePlayer", tr("Damage Player"), &m_boulder.flags, HipHop::BoulderAsset::DamagePlayer);
            auto unk0x4Prop = boulderFlagsGroup->addCheckBox("unk0x4", tr("Unknown Flag (0x4)"), &m_boulder.flags, 0x4);
            auto damageNPCsProp = boulderFlagsGroup->addCheckBox("damageNPCs", tr("Damage NPCs"), &m_boulder.flags, HipHop::BoulderAsset::DamageNPCs);
            auto unk0x10Prop = boulderFlagsGroup->addCheckBox("unk0x10", tr("Unknown Flag (0x10)"), &m_boulder.flags, 0x10);
            auto dieOnOOBSurfsProp = boulderFlagsGroup->addCheckBox("dieOnOOBSurfs", tr("Die on OOB Surfaces"), &m_boulder.flags, HipHop::BoulderAsset::DieOnOOBSurfs);
            auto unk0x40Prop = boulderFlagsGroup->addCheckBox("unk0x40", tr("Unknown Flag (0x40)"), &m_boulder.flags, 0x40);
            auto unk0x80Prop = boulderFlagsGroup->addCheckBox("unk0x80", tr("Unknown Flag (0x80)"), &m_boulder.flags, 0x80);
            auto dieOnPlayerHitProp = boulderFlagsGroup->addCheckBox("dieOnPlayerHit", tr("Die on Player Hit"), &m_boulder.flags, HipHop::BoulderAsset::DieOnPlayerHit);
            auto dieOnKillTimerProp = boulderFlagsGroup->addCheckBox("dieOnKillTimer", tr("Die on Kill Timer"), &m_boulder.flags, HipHop::BoulderAsset::DieOnKillTimer);

            boulderFlagsGroup->setExpanded(false);

            maxAngVelProp->setConvertRadiansToDegrees(true);

            HipHop::Game game = scene()->game();

            statFricProp->setVisible(game == HipHop::Game::BattleForBikiniBottom);
            volumeProp->setVisible(game == HipHop::Game::BattleForBikiniBottom);
            innerRadiusProp->setVisible(game == HipHop::Game::BattleForBikiniBottom);
            outerRadiusProp->setVisible(game == HipHop::Game::BattleForBikiniBottom);
            sphereRadiusProp->setVisible(game >= HipHop::Game::SpongeBobMovie);
            boneIndexProp->setVisible(game >= HipHop::Game::SpongeBobMovie);

            gravityProp->setHelpText(tr("The boulder's gravity."));
            massProp->setHelpText(tr("The boulder's mass."));
            bounceProp->setHelpText(tr("The boulder's bounciness."));
            frictionProp->setHelpText(tr("The boulder's friction."));
            statFricProp->setHelpText(tr("The boulder's static friction."));
            maxVelProp->setHelpText(tr("The boulder's max velocity in units/sec."));
            maxAngVelProp->setHelpText(tr("The boulder's max angular velocity in degrees."));
            stickinessProp->setHelpText(tr("The boulder's stickiness."));
            bounceDampProp->setHelpText(tr("The boulder's bounce damp amount."));
            canHitWallsProp->setHelpText(tr("If disabled, the boulder will die when it hits a wall."));
            damagePlayerProp->setHelpText(tr("If enabled, the boulder will damage the player upon contact."));
            damageNPCsProp->setHelpText(tr("If enabled, the boulder will damage NPCs upon contact."));
            dieOnOOBSurfsProp->setHelpText(tr("If enabled, the boulder will die when it touches any Surface marked as Out-of-Bounds."));
            dieOnPlayerHitProp->setHelpText(tr("If enabled, the boulder will die when the player attacks it."));
            dieOnKillTimerProp->setHelpText(tr("If enabled, the boulder will die after the time set in Kill Timer."));
            hitpointsProp->setHelpText(tr("The boulder's hit points."));
            killTimerProp->setHelpText(tr("The boulder's lifetime (Die on Kill Timer must be enabled)."));
            soundIDProp->setHelpText(tr("Sound to play when the boulder bounces."));
            volumeProp->setHelpText(tr("The sound's volume."));
            minSoundVelProp->setHelpText(tr("The minimum velocity the boulder must be traveling for the sound to play."));
            maxSoundVelProp->setHelpText(tr("The maximum velocity the boulder must be traveling for the sound to play."));
            innerRadiusProp->setHelpText(tr("The sound's inner radius."));
            outerRadiusProp->setHelpText(tr("The sound's outer radius."));

            connect(gravityProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(massProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(bounceProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(frictionProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(statFricProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(maxVelProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(maxAngVelProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(stickinessProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(bounceDampProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(killTimerProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(hitpointsProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(soundIDProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(volumeProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(minSoundVelProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(maxSoundVelProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(innerRadiusProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(outerRadiusProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(sphereRadiusProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(boneIndexProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(canHitWallsProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(damagePlayerProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(unk0x4Prop, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(damageNPCsProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(unk0x10Prop, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(dieOnOOBSurfsProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(unk0x40Prop, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(unk0x80Prop, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(dieOnPlayerHitProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);
            connect(dieOnKillTimerProp, &Inspector::Property::dataChanged, this, &BoulderAsset::makeDirty);

            inspectEntity(root);
            inspectLinks(root);
        }

        void BoulderManager::setup()
        {
            for (auto asset : assets())
            {
                ((BoulderAsset*)asset)->setup();
            }
        }

        void BoulderManager::update()
        {
            for (auto asset : assets())
            {
                ((BoulderAsset*)asset)->update();
            }
        }

        void BoulderManager::render()
        {
            for (auto asset : assets())
            {
                ((BoulderAsset*)asset)->render();
            }
        }

    }

}
