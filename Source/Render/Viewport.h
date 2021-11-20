#pragma once

#include "Render/Camera.h"

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions_2_0>

namespace Slick {

    namespace Render {

        class Viewport : public QOpenGLWidget, protected QOpenGLFunctions_2_0
        {
            Q_OBJECT
            Q_PROPERTY(Camera* camera READ camera)

        public:
            enum Buffers
            {
                ColorBuffer,
                DepthBuffer,
                StencilBuffer
            };

            Viewport(QWidget* parent = nullptr);

            Camera* camera() const { return m_camera; }

        signals:
            void initialized();

        protected:
            virtual void initializeGL() override;
            virtual void paintGL() override;
            virtual void resizeGL(int w, int h) override;

        private:
            Camera* m_camera;
        };

    }

}
