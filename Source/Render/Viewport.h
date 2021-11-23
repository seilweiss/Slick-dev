#pragma once

#include "Render/Context.h"

#include <QOpenGLWindow>
#include <QOpenGLFunctions_2_0>

namespace Slick {

    namespace Render {

        class Viewport : public QOpenGLWindow, public QOpenGLFunctions_2_0
        {
            Q_OBJECT

        public:
            Viewport(QWindow* parent = nullptr);

        protected:
            virtual void initializeGL() override;
            virtual void paintGL() override;
            virtual void resizeGL(int w, int h) override;
            virtual bool event(QEvent* e) override;

            virtual void update(float dt) = 0;
            virtual void render(Context& context) = 0;

        private:
            Context m_context;
            qint64 m_prevUpdateTime;
        };

    }

}
