#pragma once

#include <QOpenGLFunctions_2_0>

namespace Slick {

    class Viewport;
    class Camera;

    struct RenderStats
    {
        int frameCount = 0;
        int fps = 0;
        int atomicCount = 0;
    };

    class RenderContext : public QObject, public QOpenGLFunctions_2_0
    {
        Q_OBJECT

    public:
        RenderContext(QObject* parent = nullptr);

        void initialize();
        bool isInitialized() const { return m_init; }

        float deltaTime() const { return m_deltaTime; }

        Viewport* viewport() const { return m_viewport; }
        void setViewport(Viewport* viewport);

        Camera* camera() const { return m_camera; }
        void setCamera(Camera* camera);

        RenderStats& stats() { return m_stats; }

        void beginFrame();

    private:
        bool m_init;
        float m_deltaTime;
        Viewport* m_viewport;
        Camera* m_camera;
        RenderStats m_stats;
        int m_curFrameCount;
        qint64 m_prevTime;
        qint64 m_prevSecond;
    };

}
