#include "UI/ScenePanel.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QFileInfo>

namespace Slick {

    ScenePanel::ScenePanel(QWidget* parent) :
        QWidget(parent),
        m_fileTabWidget(new QTabWidget)
    {
        QVBoxLayout* mainLayout = new QVBoxLayout;

        mainLayout->addWidget(m_fileTabWidget, 1);

        setLayout(mainLayout);
    }

    void ScenePanel::setScene(Scene* scene)
    {
        m_scene = scene;

        m_fileTabWidget->clear();

        if (scene)
        {
            for (int i = 0; i < scene->fileCount(); i++)
            {
                SceneFile* file = scene->file(i);
                QString title = QFileInfo(file->path()).fileName();

                m_fileTabWidget->addTab(new QWidget, title);
            }
        }

        emit sceneChanged(scene);
    }

}
