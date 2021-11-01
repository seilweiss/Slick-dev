#pragma once

#include <QWidget>

namespace Slick {

    class ScenePanel : public QWidget
    {
        Q_OBJECT

    public:
        static ScenePanel* instance()
        {
            static ScenePanel* theInstance = new ScenePanel;
            return theInstance;
        }

    private:
        ScenePanel(QWidget* parent = nullptr);
    };

}
