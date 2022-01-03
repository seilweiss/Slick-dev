#include "render/context.h"

#include <QDateTime>

namespace Slick {

    namespace Render {

        Context::Context(QObject* parent) :
            QObject(parent),
            QOpenGLFunctions_2_0(),
            m_init(false),
            m_deltaTime(0.0f),
            m_viewport(nullptr),
            m_camera(Camera(this)),
            m_stats(),
            m_im2DWidth(640.0f),
            m_im2DHeight(480.0f),
            m_curFrameCount(0),
            m_prevTime(QDateTime::currentMSecsSinceEpoch()),
            m_prevSecond(m_prevTime)
        {
        }

        void Context::initialize()
        {
            initializeOpenGLFunctions();

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);

            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, 0.0f);

            glShadeModel(GL_SMOOTH);

            glDisable(GL_FOG);

            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);

            glEnable(GL_NORMALIZE);

            m_init = true;

            emit initialized();
        }

        void Context::beginFrame()
        {
            m_stats.atomicCount = 0;
            m_stats.triangleCount = 0;
            m_stats.frameCount++;

            m_curFrameCount++;

            qint64 time = QDateTime::currentMSecsSinceEpoch();

            m_deltaTime = (time - m_prevTime) / 1000.0f;
            m_prevTime = time;

            if (time - m_prevSecond >= 1000)
            {
                m_stats.fps = m_curFrameCount;
                m_curFrameCount = 0;
                m_prevSecond = time;
            }
        }

        void Context::beginIm2D()
        {
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0.0f, m_im2DWidth, m_im2DHeight, 0.0f, -1.0f, 1.0f);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
        }

        void Context::endIm2D()
        {
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();

            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

    }

}
