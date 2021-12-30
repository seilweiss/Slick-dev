#pragma once

#include <QWidget>

namespace Slick {

    namespace Panels {

        class ProjectPanel : public QWidget
        {
            Q_OBJECT

        public:
            static ProjectPanel* instance()
            {
                static ProjectPanel* theInstance = new ProjectPanel;
                return theInstance;
            }

        private:
            ProjectPanel(QWidget* parent = nullptr);
        };

    }

}
