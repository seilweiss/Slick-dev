#pragma once

#include <QWidget>

namespace Slick {

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
    };

}
