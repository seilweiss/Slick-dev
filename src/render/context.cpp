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
            m_curFrameCount(0),
            m_prevTime(QDateTime::currentMSecsSinceEpoch()),
            m_prevSecond(m_prevTime)
        {
        }

        void Context::initialize()
        {
            initializeOpenGLFunctions();
            m_init = true;

            emit initialized();
        }

        void Context::beginFrame()
        {
            m_stats.atomicCount = 0;
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

    }

}
