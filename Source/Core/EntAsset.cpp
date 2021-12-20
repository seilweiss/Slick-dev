#include "Core/EntAsset.h"

#include <glm/glm.hpp>

namespace Slick {

    EntAsset::EntAsset(HipHop::Asset asset, SceneFile* sceneFile) :
        BaseAsset(asset, sceneFile),
        m_entDefault(asset),
        m_ent(&m_entDefault),
        m_rotation()
    {
        setEditor(&m_entDefault);
    }

    void EntAsset::inspect(Inspector* inspector)
    {
        BaseAsset::inspect(inspector);

        m_rotation = Vector3(glm::degrees(m_ent->ang.x), glm::degrees(m_ent->ang.y), glm::degrees(m_ent->ang.z));

        auto visibleProp = inspector->group("flags")->addCheckBox("visible", &m_ent->flags, HipHop::EntAsset::Visible);

        auto transformGroup = inspector->addGroup("transform");
        auto positionProp = transformGroup->addVectorInput("position", (Vector3*)&m_ent->pos);
        auto rotationProp = transformGroup->addVectorInput("rotation", &m_rotation);
        auto scaleProp = transformGroup->addVectorInput("scale", (Vector3*)&m_ent->scale);

        connect(rotationProp, &InspectorProperty::dataChanged, this, [=]
        {
            m_ent->ang = HipHop::Vec3(glm::radians(m_rotation.x), glm::radians(m_rotation.y), glm::radians(m_rotation.z));
            makeDirty();
        });

        connect(visibleProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(positionProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(scaleProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
    }

    void EntAsset::inspectEntity(Inspector* inspector)
    {
        auto entityGroup = inspector->addGroup("entity");
        auto colorProp = entityGroup->addColorInput("color", (float*)&m_ent->redMult);
        auto modelProp = entityGroup->addAssetInput("model", &m_ent->modelInfoID, scene());
        auto animationProp = entityGroup->addAssetInput("animation", &m_ent->animListID, scene());
        auto surfaceProp = entityGroup->addAssetInput("surface", &m_ent->surfaceID, scene());
        auto preciseCollisionProp = entityGroup->addCheckBox("preciseCollision", &m_ent->moreFlags, HipHop::EntAsset::PreciseCollision);
        auto animateCollisionProp = entityGroup->addCheckBox("animateCollision", &m_ent->moreFlags, HipHop::EntAsset::AnimateCollision);
        auto recShadowsProp = entityGroup->addCheckBox("receiveShadows", &m_ent->baseFlags, HipHop::EntAsset::ReceiveShadows);
        auto csnVisibleProp = entityGroup->addCheckBox("visibleDuringCutscenes", &m_ent->baseFlags, HipHop::EntAsset::VisibleDuringCutscenes);
        auto stackableProp = entityGroup->addCheckBox("stackable", &m_ent->flags, HipHop::EntAsset::Stackable);
        auto hittableProp = entityGroup->addCheckBox("hittable", &m_ent->moreFlags, HipHop::EntAsset::Hittable);
        auto canLedgeGrabProp = entityGroup->addCheckBox("canLedgeGrab", &m_ent->moreFlags, HipHop::EntAsset::LedgeGrab);

        connect(colorProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(modelProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(animationProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(surfaceProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(stackableProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(preciseCollisionProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(hittableProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(animateCollisionProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(canLedgeGrabProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(csnVisibleProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
        connect(recShadowsProp, &InspectorProperty::dataChanged, this, &EntAsset::makeDirty);
    }

}
