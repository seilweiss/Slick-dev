#pragma once

#include "render/camera.h"

#include <QOpenGLFunctions_2_0>

namespace Slick {

    namespace Render {

        class Viewport;

        struct Stats
        {
            int frameCount = 0;
            int fps = 0;
            int atomicCount = 0;
        };

        class Context : public QObject, public QOpenGLFunctions_2_0
        {
            Q_OBJECT

        public:
            Context(QObject* object = nullptr);

            void initialize();
            bool isInitialized() const { return m_init; }

            float deltaTime() const { return m_deltaTime; }

            Viewport* viewport() const { return m_viewport; }
            void setViewport(Viewport* viewport) { m_viewport = viewport; }

            Camera* camera() { return &m_camera; }
            Stats* stats() { return &m_stats; }

            void beginFrame();

        signals:
            void initialized();

        private:
            bool m_init;
            float m_deltaTime;
            Viewport* m_viewport;
            Camera m_camera;
            Stats m_stats;
            int m_curFrameCount;
            qint64 m_prevTime;
            qint64 m_prevSecond;
        };

    }

}
