#pragma once

#include <QObject>
#include <QColor>

Q_MOC_INCLUDE("Render/Viewport.h")

namespace Slick {

    namespace Render {

        class Viewport;

        enum ClearBuffer
        {
            ColorBuffer = 0x1,
            DepthBuffer = 0x2,
            StencilBuffer = 0x4,
            AllBuffers = ColorBuffer | DepthBuffer | StencilBuffer
        };

        enum FogType
        {
            FogLinear,
            FogExp,
            FogExp2
        };

        class Camera : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(Viewport* viewport READ viewport)
            Q_PROPERTY(QColor clearColor READ clearColor WRITE setClearColor)
            Q_PROPERTY(bool fogEnabled READ fogEnabled WRITE setFogEnabled)
            Q_PROPERTY(FogType fogType READ fogType WRITE setFogType)
            Q_PROPERTY(float fogDensity READ fogDensity WRITE setFogDensity)
            Q_PROPERTY(float fogStart READ fogStart WRITE setFogStart)
            Q_PROPERTY(float fogEnd READ fogEnd WRITE setFogEnd)
            Q_PROPERTY(QColor fogColor READ fogColor WRITE setFogColor)

        public:
            Camera(Viewport* viewport);

            Viewport* viewport() const { return m_viewport; }

            QColor clearColor() const;
            void setClearColor(const QColor& color);

            void clear(int buffers);

            bool fogEnabled() const;
            void setFogEnabled(bool enabled);
            FogType fogType() const;
            void setFogType(FogType type);
            float fogDensity() const;
            void setFogDensity(float density);
            float fogStart() const;
            void setFogStart(float start);
            float fogEnd() const;
            void setFogEnd(float end);
            QColor fogColor() const;
            void setFogColor(const QColor& color);

            void applyFog();

        private:
            Viewport* m_viewport;
        };

    }

}
