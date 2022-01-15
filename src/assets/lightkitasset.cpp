#include "assets/lightkitasset.h"

#include "core/scene.h"
#include "util/mathutils.h"
#include "inspector/stllistsource.h"

#include <QDebug>
#include <QCoreApplication>

namespace Slick {

    namespace Assets {

        namespace {

            class LightPreviewProxy : public Inspector::Proxy<bool>
            {
            public:
                LightPreviewProxy(LightKitAsset* asset, int index) : m_asset(asset), m_index(index) {}

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

            class LightTypeProxy : public Inspector::Proxy<int>
            {
            public:
                LightTypeProxy(LightKitAsset* asset, int index) : m_light(&asset->serializer()->lightList[index]) {}

                virtual int data() const override
                {
                    switch (m_light->type)
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
                    case 0: m_light->type = HipHop::LightKitLight::Ambient; break;
                    case 1: m_light->type = HipHop::LightKitLight::Directional; break;
                    case 2: m_light->type = HipHop::LightKitLight::Point; break;
                    case 3: m_light->type = HipHop::LightKitLight::Spot; break;
                    }
                }

            private:
                HipHop::LightKitLight* m_light;
            };

            class LightPositionProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                LightPositionProxy(LightKitAsset* asset, int index) : m_asset(asset), m_index(index) {}

                virtual Core::Vector3 data() const override
                {
                    return m_asset->lightPosition(m_index);
                }

                virtual void setData(const Core::Vector3& pos) const override
                {
                    m_asset->setLightPosition(m_index, pos);
                }

            private:
                LightKitAsset* m_asset;
                int m_index;
            };

            class LightRotationProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                LightRotationProxy(LightKitAsset* asset, int index) : m_asset(asset), m_index(index) {}

                virtual Core::Vector3 data() const override
                {
                    return m_asset->lightRotation(m_index);
                }

                virtual void setData(const Core::Vector3& rot) const override
                {
                    m_asset->setLightRotation(m_index, rot);
                }

            private:
                LightKitAsset* m_asset;
                int m_index;
            };

            class LightScaleProxy : public Inspector::Proxy<Core::Vector3>
            {
            public:
                LightScaleProxy(LightKitAsset* asset, int index) : m_asset(asset), m_index(index) {}

                virtual Core::Vector3 data() const override
                {
                    return m_asset->lightScale(m_index);
                }

                virtual void setData(const Core::Vector3& scale) const override
                {
                    m_asset->setLightScale(m_index, scale);
                }

            private:
                LightKitAsset* m_asset;
                int m_index;
            };

            class LightListSource : public Inspector::STLListSource<std::vector<HipHop::LightKitLight>>
            {
                Q_DECLARE_TR_FUNCTIONS(LightListSource)

            public:
                LightListSource(LightKitAsset* asset) : Inspector::STLListSource<std::vector<HipHop::LightKitLight>>(asset->serializer()->lightList), m_asset(asset) {}

                virtual void createGroupItem(Inspector::Group* group, int index) override
                {
                    auto* light = &list()[index];
                    auto lightGroup = group->addGroup();
                    auto previewProp = lightGroup->addCheckBox("preview", tr("Preview"), new LightPreviewProxy(m_asset, index));
                    auto typeProp = lightGroup->addComboBox("type", tr("Type"), new LightTypeProxy(m_asset, index), { tr("Ambient"), tr("Directional"), tr("Point"), tr("Spot") });
                    auto colorProp = lightGroup->addColorInput("color", tr("Color"), (Core::ColorF*)&light->color);
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

                    auto updateProps = [=]
                    {
                        posProp->setVisible(light->type >= HipHop::LightKitLight::Directional);
                        rotProp->setVisible(light->type >= HipHop::LightKitLight::Directional);
                        scaleProp->setVisible(light->type >= HipHop::LightKitLight::Directional);
                        radiusProp->setVisible(light->type >= HipHop::LightKitLight::Point);
                        angleProp->setVisible(light->type >= HipHop::LightKitLight::Spot);
                    };

                    QObject::connect(typeProp, &Inspector::Property::dataChanged, updateProps);
                    QObject::connect(typeProp, &Inspector::Property::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(colorProp, &Inspector::Property::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(posProp, &Inspector::Property::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(rotProp, &Inspector::Property::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(scaleProp, &Inspector::Property::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(radiusProp, &Inspector::Property::dataChanged, m_asset, &LightKitAsset::makeDirty);
                    QObject::connect(angleProp, &Inspector::Property::dataChanged, m_asset, &LightKitAsset::makeDirty);

                    updateProps();
                }

            private:
                LightKitAsset* m_asset;
            };

        }

        LightKitAsset::LightKitAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            Core::Asset(asset, sceneFile),
            m_lightKit(asset)
        {
            setSerializer(&m_lightKit);
        }

        void LightKitAsset::setup()
        {
            m_lightPreviews.reserve(m_lightKit.lightList.size());
            m_lightPositions.reserve(m_lightKit.lightList.size());
            m_lightRotations.reserve(m_lightKit.lightList.size());
            m_lightScales.reserve(m_lightKit.lightList.size());

            for (const auto& light : m_lightKit.lightList)
            {
                m_lightPreviews.append(true);

                glm::mat4 mat = glm::make_mat4(light.matrix);
                glm::vec3 pos;
                glm::vec3 rot;
                glm::vec3 scale;

                Util::decomposeMatrix(mat, pos, rot, scale);

                m_lightPositions.append(Core::Vector3(pos.x, pos.y, pos.z));
                m_lightRotations.append(Core::Vector3(rot.x, rot.y, rot.z));
                m_lightScales.append(Core::Vector3(scale.x, scale.y, scale.z));
            }
        }

        void LightKitAsset::bind()
        {
            Render::Context* context = scene()->renderContext();
            float lightModelAmbient[4] = { 0, 0, 0, 0 };
            float defaultAmbient[4] = { 0, 0, 0, 0 };
            float defaultDiffuse[4] = { 0, 0, 0, 0 };
            float defaultSpecular[4] = { 0, 0, 0, 0 };
            float directionalPos[4] = { 0, 0, 1, 0 };

            context->glEnable(GL_LIGHTING);
            context->glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);

            for (int i = 0; i < 8; i++)
            {
                GLenum index = GL_LIGHT0 + i;

                if (i < m_lightKit.lightList.size() && m_lightPreviews[i])
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

        void LightKitAsset::inspect(Inspector::Root* root)
        {
            Core::Asset::inspect(root);

            auto lightKitGroup = root->addGroup("lightKit", tr("LightKit"));
            auto groupProp = lightKitGroup->addAssetInput("group", tr("Group"), &m_lightKit.groupID, scene());

            auto lightsGroup = lightKitGroup->addGroup("lights", tr("Lights"));

            lightsGroup->setListSource(new LightListSource(this));

            connect(groupProp, &Inspector::Property::dataChanged, this, &LightKitAsset::makeDirty);

            connect(lightsGroup, &Inspector::Group::listItemAdded, this, [=]
            {
                m_lightPreviews.append(true);
                m_lightPositions.append(Core::Vector3());
                m_lightRotations.append(Core::Vector3());
                m_lightScales.append(Core::Vector3(1.0f));
                makeDirty();
            });

            connect(lightsGroup, &Inspector::Group::listItemRemoved, this, [=](int index)
            {
                m_lightPreviews.removeAt(index);
                m_lightPositions.removeAt(index);
                m_lightRotations.removeAt(index);
                m_lightScales.removeAt(index);
                makeDirty();
            });
        }

        void LightKitAsset::setLightPosition(int index, const Core::Vector3& pos)
        {
            m_lightPositions[index] = pos;
            updateLightMatrix(index);
        }

        void LightKitAsset::setLightRotation(int index, const Core::Vector3& pos)
        {
            m_lightRotations[index] = pos;
            updateLightMatrix(index);
        }

        void LightKitAsset::setLightScale(int index, const Core::Vector3& pos)
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

        void LightKitManager::setup()
        {
            for (auto asset : assets())
            {
                ((LightKitAsset*)asset)->setup();
            }
        }

        void LightKitManager::bind(LightKitAsset* lightKit)
        {
            if (lightKit == m_currentLightKit)
            {
                return;
            }

            if (lightKit)
            {
                lightKit->bind();
            }
            else
            {
                Render::Context* context = scene()->renderContext();

                float ambient[4] = { 1, 1, 1, 1 };
                float diffuse[4] = { 0, 0, 0, 0 };
                float specular[4] = { 0, 0, 0, 0 };

                context->glEnable(GL_LIGHT0);
                context->glDisable(GL_LIGHT1);
                context->glDisable(GL_LIGHT2);
                context->glDisable(GL_LIGHT3);
                context->glDisable(GL_LIGHT4);
                context->glDisable(GL_LIGHT5);
                context->glDisable(GL_LIGHT6);
                context->glDisable(GL_LIGHT7);

                context->glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
                context->glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
                context->glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
            }

            m_currentLightKit = lightKit;
        }

    }

}
