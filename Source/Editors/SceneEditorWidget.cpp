#include "Editors/SceneEditorWidget.h"

#include "Editors/SceneEditorViewport.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

namespace Slick {

    SceneEditorWidget::SceneEditorWidget(QWidget* parent) :
        EditorWidget(parent),
        m_scene(nullptr),
        m_viewport(new SceneEditorViewport)
    {
        QVBoxLayout* mainLayout = new QVBoxLayout;

        QHBoxLayout* toolbar = new QHBoxLayout;

        toolbar->addWidget(new QLabel("Placeholder toolbar"));
        toolbar->addWidget(new QPushButton("Test"));
        toolbar->addWidget(new QPushButton("1"));
        toolbar->addWidget(new QPushButton("2"));
        toolbar->addWidget(new QPushButton("3"));
        toolbar->addStretch(1);
        toolbar->addWidget(new QLabel("Hello World!"));

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addLayout(toolbar);
        mainLayout->addWidget(QWidget::createWindowContainer(m_viewport), 1);

        setLayout(mainLayout);
    }

    bool SceneEditorWidget::loadScene(Scene* scene)
    {
        m_scene = scene;

        m_viewport->setScene(scene);

        return true;
    }

}
