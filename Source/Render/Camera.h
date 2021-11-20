#pragma once

#include "Render/Common.h"

#include <QObject>
#include <QColor>

namespace Slick {

    namespace Render {

        class Camera : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QColor clearColor READ clearColor WRITE setClearColor)
            Q_PROPERTY(bool fogEnabled READ fogEnabled WRITE setFogEnabled)
            Q_PROPERTY(FogType fogType READ fogType WRITE setFogType)
            Q_PROPERTY(float fogDensity READ fogDensity WRITE setFogDensity)
            Q_PROPERTY(float fogStart READ fogStart WRITE setFogStart)
            Q_PROPERTY(float fogEnd READ fogEnd WRITE setFogEnd)
            Q_PROPERTY(QColor fogColor READ fogColor WRITE setFogColor)

        public:
            Camera(QObject* parent = nullptr);

            void clear(int buffers);

            QColor clearColor() const;
            void setClearColor(const QColor& color);
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
        };

    }

}
