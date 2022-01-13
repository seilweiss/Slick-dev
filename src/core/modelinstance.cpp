#include "core/modelinstance.h"

#include "core/scene.h"
#include "core/modelbucketmanager.h"

#include "assets/lightkitasset.h"
#include "assets/fogasset.h"

#include "render/atomic.h"

namespace Slick {

    namespace Core {

        namespace {

            GLenum convertBlendFunction(uint8_t func, bool src)
            {
                switch (func)
                {
                case HipHop::PipeInfo::BlendZero: return GL_ZERO;
                case HipHop::PipeInfo::BlendOne: return GL_ONE;
                case HipHop::PipeInfo::BlendSrcColor: return GL_SRC_COLOR;
                case HipHop::PipeInfo::BlendInvSrcColor: return GL_ONE_MINUS_SRC_COLOR;
                case HipHop::PipeInfo::BlendSrcAlpha: return GL_SRC_ALPHA;
                case HipHop::PipeInfo::BlendInvSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
                case HipHop::PipeInfo::BlendDstAlpha: return GL_DST_ALPHA;
                case HipHop::PipeInfo::BlendInvDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
                case HipHop::PipeInfo::BlendDstColor: return GL_DST_COLOR;
                case HipHop::PipeInfo::BlendInvDstColor: return GL_ONE_MINUS_DST_COLOR;
                case HipHop::PipeInfo::BlendSrcAlphaSat: return GL_SRC_ALPHA_SATURATE;
                default: return src ? GL_SRC_ALPHA : GL_ONE_MINUS_SRC_ALPHA;
                }
            }

        }

        ModelInstance::ModelInstance(Scene* scene) :
            m_scene(scene),
            m_next(nullptr),
            m_data(nullptr),
            m_lightKit(nullptr),
            m_mat(1.0f),
            m_color(1.0f),
            m_visible(true),
            m_pipeInfo(nullptr)
        {
            Q_ASSERT(scene);
        }

        void ModelInstance::render()
        {
            ModelInstance* model = this;

            while (model)
            {
                if (m_scene->modelBucketManager()->isEnabled())
                {
                    m_scene->modelBucketManager()->add(model);
                }
                else
                {
                    model->renderSingle();
                }

                model = model->m_next;
            }
        }

        void ModelInstance::renderSingle()
        {
            if (!m_visible)
            {
                return;
            }

            if (!m_data)
            {
                return;
            }

            m_data->frame()->setMatrix(m_mat);

            Render::Geometry* geometry = m_data->geometry();

            for (int i = 0; i < geometry->materialCount(); i++)
            {
                geometry->material(i)->setColor(m_color);
            }

            geometry->setModulateMaterialColor(true);

            if (m_pipeInfo)
            {
                Render::Context* context = m_scene->renderContext();

                context->glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_POLYGON_BIT);

                bool lighting = true;
                bool oldFogEnabled = m_scene->fogManager()->enabled();

                switch (m_pipeInfo->Lighting)
                {
                case HipHop::PipeInfo::LightingEnabled:
                    lighting = true;
                    geometry->setPrelit(false);
                    break;
                case HipHop::PipeInfo::LightingDisabled:
                    lighting = false;
                    geometry->setPrelit(true);
                    break;
                case HipHop::PipeInfo::LightingEnabledPrelight:
                    lighting = true;
                    geometry->setPrelit(true);
                    break;
                }

                m_scene->lightKitManager()->bind(lighting ? m_lightKit : nullptr);

                context->glBlendFunc(convertBlendFunction(m_pipeInfo->BlendSrc, true),
                                     convertBlendFunction(m_pipeInfo->BlendDst, false));

                if (m_pipeInfo->ZWrite == HipHop::PipeInfo::ZWriteDisabled)
                {
                    context->glDepthMask(GL_FALSE);
                }
                else if (m_pipeInfo->ZWrite == HipHop::PipeInfo::ZWriteEnabled)
                {
                    context->glDepthMask(GL_TRUE);
                }

                if (m_pipeInfo->Cull == HipHop::PipeInfo::CullBack)
                {
                    context->glEnable(GL_CULL_FACE);
                    context->glCullFace(GL_BACK);
                }
                else if (m_pipeInfo->Cull == HipHop::PipeInfo::CullDisabled)
                {
                    context->glDisable(GL_CULL_FACE);
                }

                if (m_pipeInfo->AlphaCompare != 0)
                {
                    context->glAlphaFunc(GL_GEQUAL, m_pipeInfo->AlphaCompare / 255.0f);
                }
                else
                {
                    context->glAlphaFunc(GL_GREATER, 0.0f);
                }

                m_scene->fogManager()->setEnabled(!m_pipeInfo->DisableFog);
                m_scene->fogManager()->apply();

                if (m_pipeInfo->Cull == HipHop::PipeInfo::CullFrontThenBack)
                {
                    context->glEnable(GL_CULL_FACE);
                    context->glCullFace(GL_FRONT);
                    m_data->render();
                    context->glCullFace(GL_BACK);
                    m_data->render();
                }
                else if (m_pipeInfo->ZWrite == HipHop::PipeInfo::ZWriteDepthPrePass)
                {
                    context->glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                    m_data->render();
                    context->glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
                    m_data->render();
                }
                else
                {
                    m_data->render();
                }

                m_scene->fogManager()->setEnabled(oldFogEnabled);

                context->glPopAttrib();
            }
            else
            {
                m_scene->lightKitManager()->bind(m_lightKit);

                geometry->setPrelit(false);

                m_data->render();
            }
        }

    }

}
