#include "assets/destructobjasset.h"

#include "core/scene.h"

#include <glm/glm.hpp>

namespace Slick {

    namespace Assets {

        DestructObjAsset::DestructObjAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            EntAsset(asset, sceneFile),
            m_destructObj(asset)
        {
            setEditor(&m_destructObj);
        }

        void DestructObjAsset::setup()
        {
            EntAsset::setup();
        }

        void DestructObjAsset::update()
        {
            EntAsset::update();
        }

        void DestructObjAsset::render()
        {
            EntAsset::render();
        }

        void DestructObjAsset::inspect(Inspector::Root* root)
        {
            EntAsset::inspect(root);

            auto destructObjGroup = root->addGroup("destructibleObject", tr("Destructible Object"));
            auto animSpeedProp = destructObjGroup->addNumberInput("animSpeed", tr("Anim Speed"), &m_destructObj.animSpeed);
            auto initAnimStateProp = destructObjGroup->addNumberInput("initialAnimState", tr("Initial Anim State"), &m_destructObj.initAnimState);
            auto healthProp = destructObjGroup->addNumberInput("health", tr("Health"), &m_destructObj.health);
            auto spawnItemProp = destructObjGroup->addAssetInput("spawnItem", tr("Spawn Item"), &m_destructObj.spawnItemID, scene());
            auto dflagsProp = destructObjGroup->addNumberInput("flags", tr("Flags"), &m_destructObj.dflags);
            auto collTypeProp = destructObjGroup->addNumberInput("collisionType", tr("Collision Type"), &m_destructObj.collType);
            auto fxTypeProp = destructObjGroup->addNumberInput("fxType", tr("FX Type"), &m_destructObj.fxType);
            auto blastRadiusProp = destructObjGroup->addNumberInput("blastRadius", tr("Blast Radius"), &m_destructObj.blast_radius);
            auto blastStrengthProp = destructObjGroup->addNumberInput("blastStrength", tr("Blast Strength"), &m_destructObj.blast_strength);
            auto hitModelProp = destructObjGroup->addAssetInput("hitModel", tr("Hit Model"), &m_destructObj.hitModel, scene());
            auto hitSFXProp = destructObjGroup->addAssetInput("hitSFX", tr("Hit SFX"), &m_destructObj.sfx_hit, scene());
            auto hitShrapnelProp = destructObjGroup->addAssetInput("hitShrapnel", tr("Hit Shrapnel"), &m_destructObj.shrapnelID_hit, scene());
            auto destroyModelProp = destructObjGroup->addAssetInput("destroyModel", tr("Destroy Model"), &m_destructObj.destroyModel, scene());
            auto destroySFXProp = destructObjGroup->addAssetInput("destroySFX", tr("Destroy SFX"), &m_destructObj.sfx_destroy, scene());
            auto destroyShapnelProp = destructObjGroup->addAssetInput("destroyShrapnel", tr("Destroy Shrapnel"), &m_destructObj.shrapnelID_destroy, scene());

            HipHop::Game game = scene()->game();

            hitModelProp->setVisible(game >= HipHop::Game::BattleForBikiniBottom);
            hitSFXProp->setVisible(game >= HipHop::Game::BattleForBikiniBottom);
            hitShrapnelProp->setVisible(game >= HipHop::Game::BattleForBikiniBottom);
            destroyModelProp->setVisible(game >= HipHop::Game::BattleForBikiniBottom);
            destroySFXProp->setVisible(game >= HipHop::Game::BattleForBikiniBottom);
            destroyShapnelProp->setVisible(game >= HipHop::Game::BattleForBikiniBottom);

            connect(animSpeedProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(initAnimStateProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(healthProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(spawnItemProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(dflagsProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(collTypeProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(fxTypeProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(blastRadiusProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(blastStrengthProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(hitModelProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(hitSFXProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(hitShrapnelProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(destroyModelProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(destroySFXProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);
            connect(destroyShapnelProp, &Inspector::Property::dataChanged, this, &DestructObjAsset::makeDirty);

            inspectEntity(root);
            inspectLinks(root);
        }

        void DestructObjManager::setup()
        {
            for (auto asset : assets())
            {
                ((DestructObjAsset*)asset)->setup();
            }
        }

        void DestructObjManager::update()
        {
            for (auto asset : assets())
            {
                ((DestructObjAsset*)asset)->update();
            }
        }

        void DestructObjManager::render()
        {
            for (auto asset : assets())
            {
                ((DestructObjAsset*)asset)->render();
            }
        }

    }

}
