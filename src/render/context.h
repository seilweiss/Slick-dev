#pragma once

#include "render/camera.h"
#include "render/viewport.h"

#include <QOpenGLFunctions_2_0>

namespace Slick {

    namespace Render {

        struct Stats
        {
            int frameCount = 0;
            int fps = 0;
            int atomicCount = 0;
            int triangleCount = 0;
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

            float im2DWidth() const { return m_im2DWidth; }
            void setIm2DWidth(float width) { m_im2DWidth = width; }

            float im2DHeight() const { return m_im2DHeight; }
            void setIm2DHeight(float height) { m_im2DHeight = height; }

            bool textureFilterHackEnabled() const { return m_textureFilterHack; }
            void setTextureFilterHackEnabled(bool enabled) { m_textureFilterHack = enabled; }

            void beginFrame();
            void endFrame();

            void beginIm2D();
            void endIm2D();

        signals:
            void initialized();
            void frameEnded();

        private:
            bool m_init;
            float m_deltaTime;
            Viewport* m_viewport;
            Camera m_camera;
            Stats m_stats;
            bool m_textureFilterHack;
            float m_im2DWidth;
            float m_im2DHeight;
            int m_curFrameCount;
            qint64 m_prevTime;
            qint64 m_prevSecond;
        };

    }

}
