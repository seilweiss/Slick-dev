#include "core/scrfxmanager.h"

#include "core/scene.h"

namespace Slick {

    namespace Core {

        ScrFxManager::ScrFxManager(Scene* scene) :
            QObject(scene),
            m_scene(scene),
            m_letterBoxEnabled(false),
            m_letterBoxSize(32.0f),
            m_letterBoxAlpha(255),
            m_letterBoxCurSize(0.0f)
        {
        }

        // xScrFxUpdate
        void ScrFxManager::render()
        {
            Render::Context* context = m_scene->renderContext();

            context->glPushAttrib(GL_ALL_ATTRIB_BITS);

            context->glDisable(GL_FOG);
            context->glDisable(GL_DEPTH_TEST);
            context->glDepthMask(GL_FALSE);
            context->glEnable(GL_BLEND);
            context->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            context->glDisable(GL_LIGHTING);

            renderLetterBox();

            context->glPopAttrib();
        }

        // xScrFxUpdateLetterBox
        void ScrFxManager::renderLetterBox()
        {
            float targetSize = m_letterBoxEnabled ? m_letterBoxSize : 0.0f;

            if (m_letterBoxCurSize < targetSize)
            {
                m_letterBoxCurSize += 100.0f * m_scene->renderContext()->deltaTime();

                if (m_letterBoxCurSize > targetSize)
                {
                    m_letterBoxCurSize = targetSize;
                }
            }
            else if (m_letterBoxCurSize > targetSize)
            {
                m_letterBoxCurSize -= 100.0f * m_scene->renderContext()->deltaTime();

                if (m_letterBoxCurSize < targetSize)
                {
                    m_letterBoxCurSize = targetSize;
                }
            }

            if (m_letterBoxCurSize > 0.0f)
            {
                Render::Context* context = m_scene->renderContext();

                context->beginIm2D();

                context->glColor4f(0.0f, 0.0f, 0.0f, m_letterBoxAlpha / 255.0f);
                context->glRectf(0.0f, 0.0f, context->im2DWidth(), m_letterBoxCurSize);
                context->glRectf(0.0f, context->im2DHeight() - m_letterBoxCurSize, context->im2DWidth(), context->im2DHeight());

                context->endIm2D();
            }
        }

    }

}
