#pragma once

#include "render/context.h"
#include "render/cameracontroller.h"

#include <QOpenGLWindow>

namespace Slick {

    namespace Render {

        class Viewport : public QOpenGLWindow
        {
            Q_OBJECT
            Q_PROPERTY(Context* context READ context)
            Q_PROPERTY(CameraController* cameraController READ cameraController WRITE setCameraController)

        public:
            Viewport(QWindow* parent = nullptr);

            Context* context() { return m_context; }
            void setContext(Context* context) { m_context = context; }

            CameraController* cameraController() const { return m_camController; }
            void setCameraController(CameraController* camController);

            void captureMouse();
            void freeMouse();

        protected:
            virtual void update();
            virtual void render();

            virtual void initializeGL() override;
            virtual void paintGL() override;
            virtual void resizeGL(int w, int h) override;
            virtual bool event(QEvent* event) override;
            virtual void mousePressEvent(QMouseEvent* event) override;
            virtual void mouseReleaseEvent(QMouseEvent* event) override;
            virtual void mouseMoveEvent(QMouseEvent* event) override;
            virtual void wheelEvent(QWheelEvent* event) override;
            virtual void keyPressEvent(QKeyEvent* event) override;
            virtual void keyReleaseEvent(QKeyEvent* event) override;
            virtual void focusInEvent(QFocusEvent* event) override;
            virtual void focusOutEvent(QFocusEvent* event) override;

        private:
            Context* m_context;
            CameraController* m_camController;
            bool m_mouseCaptured;
            QPoint m_captureSaveMousePos;
            QPoint m_lastMousePos;

            QPoint center() const { return QPoint(width() / 2, height() / 2); }
        };

    }

}
