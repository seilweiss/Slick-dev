#pragma once

#include "Core/Scene.h"

#include <QWidget>

class QTabWidget;

namespace Slick {

    class ScenePanel : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)

    public:
        static ScenePanel* instance()
        {
            static ScenePanel* theInstance = new ScenePanel;
            return theInstance;
        }

        Scene* scene() const { return m_scene; }
        void setScene(Scene* scene);

    signals:
        void sceneChanged(Scene* scene);

    private:
        ScenePanel(QWidget* parent = nullptr);

        Scene* m_scene;
        QTabWidget* m_fileTabWidget;
    };

}
