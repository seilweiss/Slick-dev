#pragma once

#include <QWidget>

namespace Slick {

    class InspectorPanel : public QWidget
    {
        Q_OBJECT

    public:
        static InspectorPanel* instance()
        {
            static InspectorPanel* theInstance = new InspectorPanel;
            return theInstance;
        }

    private:
        InspectorPanel(QWidget* parent = nullptr);
    };

}
