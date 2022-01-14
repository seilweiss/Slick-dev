#pragma once

#include <QWidget>

class QLabel;

namespace Slick {

    namespace Render { class Context; }

    namespace Panels {

        class DebugPanel : public QWidget
        {
            Q_OBJECT

        public:
            static DebugPanel* instance()
            {
                static DebugPanel* theInstance = new DebugPanel;
                return theInstance;
            }

            void setRenderContext(Render::Context* context);

            void refresh();

        private:
            DebugPanel(QWidget* parent = nullptr);

            Render::Context* m_context;
            QLabel* m_debugLabel;
        };

    }

}
