#include "Assets/LightKitAsset.h"

#include <QDebug>
#include <QCoreApplication>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Slick {

    namespace Assets {

        namespace {

            class LightPreviewProxy : public InspectorProxy<bool>
            {
            public:
                LightPreviewProxy(LightKitAsset* asset, int index) : InspectorProxy(nullptr), m_asset(asset), m_index(index) {}

                virtual bool data() const override
                {
                    return m_asset->lightPreviewEnabled(m_index);
                }

                virtual void setData(const bool& enabled) const override
                {
                    m_asset->setLightPreviewEnabled(m_index, enabled);
                }

            private:
                LightKitAsset* m_asset;
                int m_index;
            };

            class LightTypeProxy : public InspectorProxy<int, uint32_t>
            {
            public:
                LightTypeProxy(uint32_t* source) : InspectorProxy(source) {}

                virtual int data() const override
                {
                    switch (*source())
                    {
                    case HipHop::LightKitLight::Ambient: return 0;
                    case HipHop::LightKitLight::Directional: return 1;
                    case HipHop::LightKitLight::Point: return 2;
                    case HipHop::LightKitLight::Spot: return 3;
                    default: return -1;
                    }
                }

                virtual void setData(const int& type) const override
                {
                    switch (type)
                    {
                    case 0: *source() = HipHop::LightKitLight::Ambient; break;
                    case 1: *source() = HipHop::LightKitLight::Directional; break;
                    case 2: *source() = HipHop::LightKitLight::Point; break;
                    case 3: *source() = HipHop::LightKitLight::Spot; break;
                    }
                }
            };

            class LightPositionProxy : public InspectorProxy<Vector3>
            {
            public:
                LightPositionProxy(LightKitAsset* asset, int index) : InspectorProxy(nullptr), m_asset(asset), m_index(index) {}

                virtual Vector3 data() const override
                {
                    return m_asset->lightPosition(m_index);
                }

                virtual void setData(const Vector3& pos) const override
                {
                    m_asset->setLightPosition(m_index, pos);
                }

            private:
                LightKitAsset* m_asset;
                int m_index;
            };

            class LightRotationProxy : public InspectorProxy<Vector3>
            {
            public:
                LightRotationProxy(LightKitAsset* asset, int index) : InspectorProxy(nullptr), m_asset(asset), m_index(index) {}

                virtual Vector3 data() const override
                {
                    return m_asset->lightRotation(m_index);
                }

                virtual void setData(const Vector3& rot) const override
                {
                    m_asset->setLightRotation(m_index, rot);
                }

            private:
                LightKitAsset* m_asset;
                int m_index;
            };

            class LightScaleProxy : public InspectorProxy<Vector3>
            {
            public:
                LightScaleProxy(LightKitAsset* asset, int index) : InspectorProxy(nullptr), m_asset(asset), m_index(index) {}

                virtual Vector3 data() const override
                {
                    return m_asset->lightScale(m_index);
                }

                virtual void setData(const Vector3& rot) const override
                {
                    m_asset->setLightScale(m_index, rot);
                }

            private:
                LightKitAsset* m_asset;
                int m_index;
            };

            class LightListSource : public InspectorListSource<std::vector<HipHop::LightKitLight>>
            {
                Q_DECLARE_TR_FUNCTIONS(LightListSource)

            public:
                LightListSource(LightKitAsset* asset, std::vector<HipHop::LightKitLight>& list) : InspectorListSource(list), m_asset(asset) {}

                virtual void createGroupItem(InspectorGroup* group, int index) override
                {
                    auto* light = &list()[index];
                    auto lightGroup = group->addGroup();
                    auto previewProp = lightGroup->addCheckBox("preview", tr("Preview"), new LightPreviewProxy(m_asset, index));
                    auto typeProp = lightGroup->addComboBox("type", tr("Type"), new LightTypeProxy(&light->type), { tr("Ambient"), tr("Directional"), tr("Point"), tr("Spot") });
                    auto colorProp = lightGroup->addColorInput("color", tr("Color"), (ColorF*)&light->color);
                    auto posProp = lightGroup->addVectorInput("position", tr("Position"), new LightPositionProxy(m_asset, index));
                    auto rotProp = lightGroup->addVectorInput("rotation", tr("Rotation"), new LightRotationProxy(m_asset, index));
                    auto scaleProp = lightGroup->addVectorInput("scale", tr("Scale"), new LightScaleProxy(m_asset, index));
                    auto radiusProp = lightGroup->addNumberInput("radius", tr("Radius"), &light->radius);
                    auto angleProp = lightGroup->addNumberInput("coneAngle", tr("Cone Angle"), &light->angle);

                    rotProp->setConvertRadiansToDegrees(true);

                    previewProp->setHelpText(tr("Activates the light in the editor viewport."));
                    typeProp->setHelpText(tr("The light's type."));
                    colorProp->setHelpText(tr("The light's color."));
                    posProp->setHelpText(tr("The light's position."));
                    rotProp->setHelpText(tr("The light's rotation."));
                    scaleProp->setHelpText(tr("The light's scale."));
                    radiusProp->setHelpText(tr("The light's radius."));
                    angleProp->setHelpText(tr("The light's cone angle."));

                    QObject::connect(typeProp, &InspectorProperty::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(colorProp, &InspectorProperty::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(posProp, &InspectorProperty::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(rotProp, &InspectorProperty::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(scaleProp, &InspectorProperty::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(radiusProp, &InspectorProperty::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(angleProp, &InspectorProperty::dataChanged, m_asset, &LightKitAsset::makeDirty);
                }

            private:
                LightKitAsset* m_asset;
            };

        }

        LightKitAsset::LightKitAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_lightKit(asset)
        {
            setEditor(&m_lightKit);
        }

        void LightKitAsset::bind(RenderContext* context)
        {
            float lightModelAmbient[4] = { 0, 0, 0, 0 };
            float defaultAmbient[4] = { 0, 0, 0, 0 };
            float defaultDiffuse[4] = { 0, 0, 0, 0 };
            float defaultSpecular[4] = { 0, 0, 0, 0 };
            float directionalPos[4] = { 0, 0, 1, 0 };

            context->glPushAttrib(GL_LIGHTING_BIT);
            context->glEnable(GL_LIGHTING);
            context->glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);

            for (int i = 0; i < m_lightKit.lightList.size(); i++)
            {
                GLenum index = GL_LIGHT0 + i;

                if (m_lightPreviews[i])
                {
                    context->glEnable(index);

                    auto& light = m_lightKit.lightList[i];

                    switch (light.type)
                    {
                    case HipHop::LightKitLight::Ambient:
                    {
                        context->glLightfv(index, GL_AMBIENT, light.color);
                        context->glLightfv(index, GL_DIFFUSE, defaultDiffuse);
                        context->glLightfv(index, GL_SPECULAR, defaultSpecular);
                        break;
                    }
                    case HipHop::LightKitLight::Directional:
                    {
                        context->glPushMatrix();
                        context->glMultMatrixf(light.matrix);

                        context->glLightfv(index, GL_AMBIENT, defaultAmbient);
                        context->glLightfv(index, GL_DIFFUSE, light.color);
                        context->glLightfv(index, GL_SPECULAR, defaultSpecular);
                        context->glLightfv(index, GL_POSITION, directionalPos);

                        context->glPopMatrix();
                        break;
                    }
                    default:
                    {
                        context->glLightfv(index, GL_AMBIENT, defaultAmbient);
                        context->glLightfv(index, GL_DIFFUSE, defaultDiffuse);
                        context->glLightfv(index, GL_SPECULAR, defaultSpecular);
                        break;
                    }
                    }
                }
                else
                {
                    context->glDisable(index);
                }
            }
        }

        void LightKitAsset::unbind(RenderContext* context)
        {
            context->glPopAttrib();
        }

        void LightKitAsset::postLoad()
        {
            m_lightPreviews.reserve(m_lightKit.lightList.size());
            m_lightPositions.reserve(m_lightKit.lightList.size());
            m_lightRotations.reserve(m_lightKit.lightList.size());
            m_lightScales.reserve(m_lightKit.lightList.size());

            for (const auto& light : m_lightKit.lightList)
            {
                m_lightPreviews.append(true);

                glm::mat4 mat = glm::make_mat4(light.matrix);
                glm::vec3 scale;
                glm::quat rot;
                glm::vec3 pos;
                glm::vec3 skew;
                glm::vec4 persp;

                glm::decompose(mat, scale, rot, pos, skew, persp);

                //rot = glm::conjugate(rot);

                glm::vec3 euler = glm::eulerAngles(rot);

                m_lightPositions.append(Vector3(pos.x, pos.y, pos.z));
                m_lightRotations.append(Vector3(euler.x, euler.y, euler.z));
                m_lightScales.append(Vector3(scale.x, scale.y, scale.z));
            }
        }

        void LightKitAsset::inspect(Inspector* inspector)
        {
            Asset::inspect(inspector);

            auto lightKitGroup = inspector->addGroup("lightKit", tr("LightKit"));
            auto groupProp = lightKitGroup->addAssetInput("group", tr("Group"), &m_lightKit.groupID, scene());

            auto lightsGroup = lightKitGroup->addGroup("lights", tr("Lights"));

            lightsGroup->setListSource(new LightListSource(this, m_lightKit.lightList));

            connect(groupProp, &InspectorProperty::dataChanged, this, &LightKitAsset::makeDirty);

            connect(lightsGroup, &InspectorGroup::listItemAdded, this, [=]
            {
                m_lightPreviews.append(true);
                m_lightPositions.append(Vector3());
                m_lightRotations.append(Vector3());
                m_lightScales.append(Vector3(1.0f));
                makeDirty();
            });

            connect(lightsGroup, &InspectorGroup::listItemRemoved, this, [=](int index)
            {
                m_lightPreviews.removeAt(index);
                m_lightPositions.removeAt(index);
                m_lightRotations.removeAt(index);
                m_lightScales.removeAt(index);
                makeDirty();
            });
        }

        void LightKitAsset::setLightPosition(int index, const Vector3& pos)
        {
            m_lightPositions[index] = pos;
            updateLightMatrix(index);
        }

        void LightKitAsset::setLightRotation(int index, const Vector3& pos)
        {
            m_lightRotations[index] = pos;
            updateLightMatrix(index);
        }

        void LightKitAsset::setLightScale(int index, const Vector3& pos)
        {
            m_lightScales[index] = pos;
            updateLightMatrix(index);
        }

        void LightKitAsset::updateLightMatrix(int index)
        {
            glm::mat4 mat(1.0f);

            mat = glm::scale(mat, glm::vec3(m_lightScales[index].x, m_lightScales[index].y, m_lightScales[index].z));
            mat *= glm::mat4_cast(glm::quat(glm::vec3(m_lightRotations[index].x, m_lightRotations[index].y, m_lightRotations[index].z)));
            mat = glm::translate(mat, glm::vec3(m_lightPositions[index].x, m_lightPositions[index].y, m_lightPositions[index].z));

            memcpy(m_lightKit.lightList[index].matrix, glm::value_ptr(mat), sizeof(float) * 16);
        }

    }

}
