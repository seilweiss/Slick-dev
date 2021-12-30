#pragma once

#include <QWidget>

class QPushButton;

namespace Slick {

    namespace Panels {

        class ToolbarPanel : public QWidget
        {
            Q_OBJECT

        public:
            static ToolbarPanel* instance()
            {
                static ToolbarPanel* theInstance = new ToolbarPanel;
                return theInstance;
            }

        private:
            ToolbarPanel(QWidget* parent = nullptr);

            QPushButton* m_playButton;
        };

    }

}
