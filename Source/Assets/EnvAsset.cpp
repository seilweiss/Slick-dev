#include "Assets/EnvAsset.h"

#include "Assets/JSPAsset.h"
#include "Assets/LightKitAsset.h"
#include "Core/Scene.h"

namespace Slick {

    namespace Assets {

        EnvAsset::EnvAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_env(asset),
            m_jspInfo(nullptr),
            m_objLightKit(nullptr)
        {
            setEditor(&m_env);
        }

        void EnvAsset::inspect(Inspector* inspector)
        {
            BaseAsset::inspect(inspector);

            auto envGroup = inspector->addGroup("environment", tr("Environment"));
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

            connect(bspProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(startCameraProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(climateFlagsProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(climateStrengthMinProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(climateStrengthMaxProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspLightKitProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(objectLightKitProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspCollisionProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspFXProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspCameraProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspMapperProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspMapperCollisionProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(bspMapperFXProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);
            connect(loldHeightProp, &InspectorProperty::dataChanged, this, &EnvAsset::makeDirty);

            inspectLinks(inspector);
        }

        void EnvAsset::setup()
        {
            m_jspInfo = qobject_cast<JSPAsset*>(scene()->asset(m_env.bspAssetID));
            m_objLightKit = qobject_cast<LightKitAsset*>(scene()->asset(m_env.objectLightKit));
        }

        void EnvAsset::render(RenderContext* context)
        {
            if (m_jspInfo)
            {
                m_jspInfo->render(context);
            }
        }

    }

}
