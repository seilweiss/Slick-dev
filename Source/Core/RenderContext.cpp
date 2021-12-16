#include "Core/RenderContext.h"

#include <QDateTime>

namespace Slick {

    RenderContext::RenderContext(QObject* parent) :
        QObject(parent),
        QOpenGLFunctions_2_0(),
        m_viewport(nullptr),
        m_camera(nullptr),
        m_stats(),
        m_curFrameCount(0),
        m_prevTime(QDateTime::currentMSecsSinceEpoch()),
        m_prevSecond(m_prevTime)
    {
    }

    void RenderContext::initialize()
    {
        initializeOpenGLFunctions();
        m_init = true;
    }

    void RenderContext::setViewport(Viewport* viewport)
    {
        m_viewport = viewport;
    }

    void RenderContext::setCamera(Camera* camera)
    {
        m_camera = camera;
    }

    void RenderContext::beginFrame()
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
