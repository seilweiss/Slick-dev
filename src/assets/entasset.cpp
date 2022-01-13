#include "assets/entasset.h"

#include "core/scene.h"
#include "assets/modelasset.h"
#include "assets/envasset.h"
#include "assets/lightkitasset.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Slick {

    namespace Assets {

        EntAsset::EntAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_entDefault(asset),
            m_ent(&m_entDefault),
            m_model(nullptr),
            m_lightKit(nullptr),
            m_renderEnabled(true)
        {
            setEditor(&m_entDefault);
        }

        void EntAsset::setup()
        {
            Assets::ModelAsset* modelAsset = qobject_cast<Assets::ModelAsset*>(scene()->assetById(m_ent->modelInfoID));

            if (modelAsset)
            {
                m_model = modelAsset->createInstance();
            }

            Assets::EnvAsset* envAsset = qobject_cast<Assets::EnvAsset*>(scene()->assetByType(HipHop::AssetType::ENV));

            if (envAsset)
            {
                m_lightKit = envAsset->objectLightKit();
            }
        }

        void EntAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto visibleProp = root->group("flags")->addCheckBox("visible", tr("Visible"), &m_ent->flags, HipHop::EntAsset::Visible);

            auto transformGroup = root->addGroup("transform", tr("Transform"));
            auto positionProp = transformGroup->addVectorInput("position", tr("Position"), (Core::Vector3*)&m_ent->pos);
            auto rotationProp = transformGroup->addVectorInput("rotation", tr("Rotation"), (Core::Vector3*)&m_ent->ang);
            auto scaleProp = transformGroup->addVectorInput("scale", tr("Scale"), (Core::Vector3*)&m_ent->scale);

            rotationProp->setConvertRadiansToDegrees(true);

            visibleProp->setHelpText(tr("Whether the object is visible or not.\n"
                                        "Visible means the object will be rendered and can also affect\n"
                                        "whether the object is active or not, depending on the asset type."));
            positionProp->setHelpText(tr("The entity's position."));
            rotationProp->setHelpText(tr("The entity's rotation in degrees."));
            scaleProp->setHelpText(tr("The entity's scale.\n"
                                      "Note: it is recommended to have a uniform scale (all axes are the same),\n"
                                      "as non-uniform scaling tends to cause buggy collision or lighting."));

            connect(visibleProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(positionProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(rotationProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(scaleProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
        }

        void EntAsset::inspectEntity(Inspector::Root* root)
        {
            auto entityGroup = root->addGroup("entity", tr("Entity"));
            auto colorProp = entityGroup->addColorInput("color", tr("Color"), (float*)&m_ent->redMult);
            auto modelProp = entityGroup->addAssetInput("model", tr("Model"), &m_ent->modelInfoID, scene());
            auto animationProp = entityGroup->addAssetInput("animation", tr("Animation"), &m_ent->animListID, scene());
            auto surfaceProp = entityGroup->addAssetInput("surface", tr("Surface"), &m_ent->surfaceID, scene());
            auto preciseCollisionProp = entityGroup->addCheckBox("preciseCollision", tr("Precise Collision"), &m_ent->moreFlags, HipHop::EntAsset::PreciseCollision);
            auto animateCollisionProp = entityGroup->addCheckBox("animateCollision", tr("Animate Collision"), &m_ent->moreFlags, HipHop::EntAsset::AnimateCollision);
            auto recShadowsProp = entityGroup->addCheckBox("receiveShadows", tr("Receive Shadows"), &m_ent->baseFlags, HipHop::EntAsset::ReceiveShadows);
            auto csnVisibleProp = entityGroup->addCheckBox("visibleDuringCutscenes", tr("Visible During Cutscenes"), &m_ent->baseFlags, HipHop::EntAsset::VisibleDuringCutscenes);
            auto stackableProp = entityGroup->addCheckBox("stackable", tr("Stackable"), &m_ent->flags, HipHop::EntAsset::Stackable);
            auto hittableProp = entityGroup->addCheckBox("hittable", tr("Hittable"), &m_ent->moreFlags, HipHop::EntAsset::Hittable);
            auto canLedgeGrabProp = entityGroup->addCheckBox("canLedgeGrab", tr("Can Ledge Grab"), &m_ent->moreFlags, HipHop::EntAsset::LedgeGrab);

            colorProp->setHelpText(tr("The entity's color.\n"
                                      "Note: due to a bug in BfBB, the color will change to white/fully opaque\n"
                                      "if the scene is reset (e.g. due to the player dying)."));
            modelProp->setHelpText(tr("The entity's model used for rendering. It can be either a Model or\n"
                                      "Model Info asset."));
            animationProp->setHelpText(tr("The entity's animation. It can be either an Animation or\n"
                                          "Animation List asset."));
            surfaceProp->setHelpText(tr("The entity's surface."));
            preciseCollisionProp->setHelpText(tr("If enabled, collisions will be accurate to the model's mesh.\n"
                                                 "If disabled, collisions will use the model's bounding sphere or box (depending on the asset type)."));
            animateCollisionProp->setHelpText(tr("If enabled, the entity's collision follows its current animation.\n"
                                                 "Precise Collision should also be enabled."));
            recShadowsProp->setHelpText(tr("If enabled, the entity will receive shadows from other entities\n"
                                           "that cast shadows (e.g. Player, NPC, Pickup)"));
            csnVisibleProp->setHelpText(tr("If enabled, the entity will be visible while a cutscene is playing."));
            stackableProp->setHelpText(tr("Whether the entity is stackable or not.\n"
                                          "Stackable means the entity will automatically move down to sit\n"
                                          "on top of whatever is below it.\n"
                                          "Note: does not work with Simple Objects."));
            hittableProp->setHelpText(tr("Whether the entity is hittable or not.\n"
                                         "Hittable means the entity will receive Hit events when hit by the player.\n"
                                         "This does not need to be enabled manually in most cases; it will be enabled\n"
                                         "in-game automatically depending on the asset type and the asset's Links."));
            canLedgeGrabProp->setHelpText(tr("If enabled, the player can ledge grab this entity.\n"
                                             "Precise Collision must also be enabled."));

            connect(colorProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(modelProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(animationProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(surfaceProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(preciseCollisionProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(animateCollisionProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(recShadowsProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(csnVisibleProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(stackableProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(hittableProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
            connect(canLedgeGrabProp, &Inspector::Property::dataChanged, this, &EntAsset::makeDirty);
        }

        void EntAsset::update()
        {
            if (!m_model)
            {
                return;
            }

            glm::mat4 mat(1.0f);

            mat = glm::translate(mat, glm::vec3(m_ent->pos.x, m_ent->pos.y, m_ent->pos.z));
            mat *= glm::eulerAngleYXZ(m_ent->ang.x, m_ent->ang.y, m_ent->ang.z);
            mat = glm::scale(mat, glm::vec3(m_ent->scale.x, m_ent->scale.y, m_ent->scale.z));

            Core::ModelInstance* curModel = m_model;

            while (curModel)
            {
                curModel->setMatrix(mat);
                curModel->setColor(glm::vec4(m_ent->redMult, m_ent->greenMult, m_ent->blueMult, m_ent->seeThru));

                curModel = curModel->next();
            }
        }

        void EntAsset::render()
        {
            if (!m_renderEnabled)
            {
                return;
            }

            if (!(m_ent->flags & HipHop::EntAsset::Visible))
            {
                return;
            }

            if (!m_model)
            {
                return;
            }

            m_model->setLightKit(m_lightKit);
            m_model->render();
        }

    }

}
