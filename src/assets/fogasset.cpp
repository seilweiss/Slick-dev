#include "assets/fogasset.h"

#include "core/scene.h"
#include "render/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    namespace Assets {

        FogAsset::FogAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_fog(asset)
        {
            setEditor(&m_fog);
        }

        void FogAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto fogGroup = root->addGroup("fog", tr("Fog"));
            auto fogTypeProp = fogGroup->addNumberInput("type", tr("Type"), &m_fog.fogType);
            auto fogColorProp = fogGroup->addColorInput("fogColor", tr("Fog Color"), (Core::Color*)&m_fog.fogColor);
            auto bkgndColorProp = fogGroup->addColorInput("backgroundColor", tr("Background Color"), (Core::Color*)&m_fog.bkgndColor);
            auto fogStartProp = fogGroup->addNumberInput("startDistance", tr("Start Distance"), &m_fog.fogStart);
            auto fogStopProp = fogGroup->addNumberInput("endDistance", tr("End Distance"), &m_fog.fogStop);
            auto fogDensityProp = fogGroup->addNumberInput("density", tr("Density"), &m_fog.fogDensity);
            auto transitionTimeProp = fogGroup->addNumberInput("transitionTime", tr("Transition Time"), &m_fog.transitionTime);

            fogColorProp->setHelpText(tr("The fog's color."));
            bkgndColorProp->setHelpText(tr("The fog's background color (camera's clear color)."));
            fogStartProp->setHelpText(tr("The fog's start distance from the camera."));
            fogStopProp->setHelpText(tr("The fog's end distance from the camera (camera's near clipping plane)."));
            fogDensityProp->setHelpText(tr("The fog's density."));

            connect(fogTypeProp, &Inspector::Property::dataChanged, this, &FogAsset::makeDirty);
            connect(fogColorProp, &Inspector::Property::dataChanged, this, &FogAsset::makeDirty);
            connect(bkgndColorProp, &Inspector::Property::dataChanged, this, &FogAsset::makeDirty);
            connect(fogStartProp, &Inspector::Property::dataChanged, this, &FogAsset::makeDirty);
            connect(fogStopProp, &Inspector::Property::dataChanged, this, &FogAsset::makeDirty);
            connect(fogDensityProp, &Inspector::Property::dataChanged, this, &FogAsset::makeDirty);
            connect(transitionTimeProp, &Inspector::Property::dataChanged, this, &FogAsset::makeDirty);

            inspectLinks(root);
        }

        void FogAsset::apply()
        {
            Render::Context* context = scene()->renderContext();

            glm::vec4 fogColor = glm::vec4(m_fog.fogColor[0] / 255.0f,
                                           m_fog.fogColor[1] / 255.0f,
                                           m_fog.fogColor[2] / 255.0f,
                                           m_fog.fogColor[3] / 255.0f);

            glm::vec4 clearColor = glm::vec4(m_fog.bkgndColor[0] / 255.0f,
                                             m_fog.bkgndColor[1] / 255.0f,
                                             m_fog.bkgndColor[2] / 255.0f,
                                             m_fog.bkgndColor[3] / 255.0f);

            context->glEnable(GL_FOG);
            context->glFogi(GL_FOG_MODE, GL_LINEAR);
            context->glFogf(GL_FOG_DENSITY, m_fog.fogDensity);
            context->glFogf(GL_FOG_START, m_fog.fogStart);
            context->glFogf(GL_FOG_END, m_fog.fogStop);
            context->glFogfv(GL_FOG_COLOR, glm::value_ptr(fogColor));
            context->glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

            Render::Projection proj = context->camera()->projection();
            proj.farClip = m_fog.fogStop;
            context->camera()->setProjection(proj);
        }

        void FogManager::setPreviewFog(Assets::FogAsset* fog)
        {
            if (m_previewFog)
            {
                m_previewFog->disconnect(this);
            }

            m_previewFog = fog;

            connect(m_previewFog, &QObject::destroyed, this, [=]
            {
                m_previewFog = nullptr;
                emit previewFogChanged(nullptr);
            });

            emit previewFogChanged(fog);
        }

        void FogManager::setup()
        {
            m_previewFog = !assets().empty() ? (FogAsset*)assets()[0] : nullptr;
        }

        void FogManager::apply()
        {
            if (m_previewFog)
            {
                m_previewFog->apply();
            }
            else
            {
                Render::Context* context = scene()->renderContext();

                context->glDisable(GL_FOG);
                context->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

                Render::Projection proj = context->camera()->projection();
                proj.farClip = 1000.0f;
                context->camera()->setProjection(proj);
            }
        }

    }

}
