#include "assets/envasset.h"

#include "assets/jspasset.h"
#include "assets/lightkitasset.h"
#include "core/scene.h"

namespace Slick {

    namespace Assets {

        EnvAsset::EnvAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_env(asset),
            m_jspInfo(nullptr),
            m_objLightKit(nullptr)
        {
            setEditor(&m_env);
        }

        void EnvAsset::setup()
        {
            m_jspInfo = qobject_cast<JSPAsset*>(scene()->asset(m_env.bspAssetID));
            m_objLightKit = qobject_cast<LightKitAsset*>(scene()->asset(m_env.objectLightKit));
        }

        void EnvAsset::render()
        {
            if (m_jspInfo)
            {
                m_jspInfo->render();
            }
        }

        void EnvAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto envGroup = root->addGroup("environment", tr("Environment"));
            auto bspProp = envGroup->addAssetInput("bsp", tr("BSP"), &m_env.bspAssetID, scene());
            auto startCameraProp = envGroup->addAssetInput("startCamera", tr("Start Camera"), &m_env.startCameraAssetID, scene());
            auto climateFlagsProp = envGroup->addNumberInput("climateFlags", tr("Climate Flags"), &m_env.climateFlags);
            auto climateStrengthMinProp = envGroup->addNumberInput("climateStrengthMin", tr("Climate Strength Min"), &m_env.climateStrengthMin);
            auto climateStrengthMaxProp = envGroup->addNumberInput("climateStrengthMax", tr("Climate Strength Max"), &m_env.climateStrengthMax);
            auto bspLightKitProp = envGroup->addAssetInput("bspLightKit", tr("BSP LightKit"), &m_env.bspLightKit, scene());
            auto objectLightKitProp = envGroup->addAssetInput("objectLightKit", tr("Object LightKit"), &m_env.objectLightKit, scene());
            auto bspCollisionProp = envGroup->addAssetInput("bspCollision", tr("BSP Collision"), &m_env.bspCollisionAssetID, scene());
            auto bspFXProp = envGroup->addAssetInput("bspFX", tr("BSP FX"), &m_env.bspFXAssetID, scene());
            auto bspCameraProp = envGroup->addAssetInput("bspCamera", tr("BSP Camera"), &m_env.bspCameraAssetID, scene());
            auto bspMapperProp = envGroup->addAssetInput("bspMapper", tr("BSP Mapper"), &m_env.bspMapperID, scene());
            auto bspMapperCollisionProp = envGroup->addAssetInput("bspMapperCollision", tr("BSP Mapper Collision"), &m_env.bspMapperID, scene());
            auto bspMapperFXProp = envGroup->addAssetInput("bspMapperFX", tr("BSP Mapper FX"), &m_env.bspMapperID, scene());
            auto loldHeightProp = envGroup->addNumberInput("loldHeight", tr("Lold Height"), &m_env.loldHeight);

            connect(bspProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(startCameraProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(climateFlagsProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(climateStrengthMinProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(climateStrengthMaxProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspLightKitProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(objectLightKitProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspCollisionProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspFXProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspCameraProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspMapperProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspMapperCollisionProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspMapperFXProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);
            connect(loldHeightProp, &Inspector::Property::dataChanged, this, &EnvAsset::makeDirty);

            inspectLinks(root);
        }

        void EnvManager::setup()
        {
            for (auto asset : assets())
            {
                ((EnvAsset*)asset)->setup();
            }
        }

        void EnvManager::render()
        {
            for (auto asset : assets())
            {
                ((EnvAsset*)asset)->render();
            }
        }

    }

}
