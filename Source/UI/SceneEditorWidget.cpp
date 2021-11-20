#include "UI/SceneEditorWidget.h"

#include "Render/Viewport.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

namespace Slick {

    SceneEditorWidget::SceneEditorWidget(QWidget* parent) :
        IEditorWidget(parent),
        m_scene(nullptr),
        m_viewport(new Render::Viewport)
    {
        connect(m_viewport, &Render::Viewport::initialized, this, [=]
        {
            m_scene->render(m_viewport);
        });

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
        mainLayout->addWidget(m_viewport, 1);

        setLayout(mainLayout);
    }

    bool SceneEditorWidget::loadScene(Scene* scene)
    {
        m_scene = scene;

        return true;
    }

}
