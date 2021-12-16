#include "Assets/FogAsset.h"

#include "Core/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Slick {

    namespace Assets {

        FogAsset::FogAsset(HipHop::Asset asset, SceneFile* sceneFile) :
            Asset(asset, sceneFile),
            m_fog(asset)
        {
            m_fog.Load();

            auto fogGroup = inspector()->addGroup("fog");
            auto fogTypeProp = fogGroup->addNumber("type", &m_fog.fogType);
            auto fogColorProp = fogGroup->addColor("fogColor", &m_fog.fogColor);
            auto bkgndColorProp = fogGroup->addColor("backgroundColor", &m_fog.bkgndColor);
            auto fogStartProp = fogGroup->addNumber("startDistance", &m_fog.fogStart);
            auto fogStopProp = fogGroup->addNumber("endDistance", &m_fog.fogStop);
            auto fogDensityProp = fogGroup->addNumber("density", &m_fog.fogDensity);
            auto transitionTimeProp = fogGroup->addNumber("transitionTime", &m_fog.transitionTime);

            connect(fogTypeProp, &InspectorProperty::dataChanged, this, &FogAsset::makeDirty);
            connect(fogColorProp, &InspectorProperty::dataChanged, this, &FogAsset::makeDirty);
            connect(bkgndColorProp, &InspectorProperty::dataChanged, this, &FogAsset::makeDirty);
            connect(fogStartProp, &InspectorProperty::dataChanged, this, &FogAsset::makeDirty);
            connect(fogStopProp, &InspectorProperty::dataChanged, this, &FogAsset::makeDirty);
            connect(fogDensityProp, &InspectorProperty::dataChanged, this, &FogAsset::makeDirty);
            connect(transitionTimeProp, &InspectorProperty::dataChanged, this, &FogAsset::makeDirty);
        }

        void FogAsset::doSave()
        {
            m_fog.Save();
        }

        void FogAsset::apply(RenderContext* context)
        {
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

            Projection proj = context->camera()->projection();
            proj.farClip = m_fog.fogStop;
            context->camera()->setProjection(proj);
        }

    }

}
