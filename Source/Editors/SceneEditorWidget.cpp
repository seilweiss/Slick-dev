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
        m_context(new RenderContext(this)),
        m_viewport(new SceneEditorViewport(m_context)),
        m_statsLabel(new QLabel)
    {
        m_context->setViewport(m_viewport);
        m_context->setCamera(new Camera(m_context));

        QVBoxLayout* mainLayout = new QVBoxLayout;

        QHBoxLayout* toolbar = new QHBoxLayout;

        toolbar->addWidget(new QLabel("Placeholder toolbar"));
        toolbar->addWidget(new QPushButton("Test"));
        toolbar->addWidget(new QPushButton("1"));
        toolbar->addWidget(new QPushButton("2"));
        toolbar->addWidget(new QPushButton("3"));
        toolbar->addStretch(1);
        toolbar->addWidget(m_statsLabel);

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addLayout(toolbar);
        mainLayout->addWidget(QWidget::createWindowContainer(m_viewport), 1);

        setLayout(mainLayout);

        connect(m_viewport, &SceneEditorViewport::doneRendering, this, &SceneEditorWidget::updateStats);
    }

    void SceneEditorWidget::setScene(Scene* scene)
    {
        m_scene = scene;

        m_viewport->setScene(scene);
    }

    void SceneEditorWidget::updateStats()
    {
        RenderStats& stats = m_context->stats();

        m_statsLabel->setText(tr("Atomics: %1 FPS: %2").arg(stats.atomicCount).arg(stats.fps));
    }

}
