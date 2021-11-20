#include "UI/SceneEditorWidget.h"

#include "Render/Viewport.h"

#include <QHBoxLayout>

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

        QHBoxLayout* mainLayout = new QHBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addWidget(m_viewport, 1);

        setLayout(mainLayout);
    }

    bool SceneEditorWidget::loadScene(Scene* scene)
    {
        m_scene = scene;

        return true;
    }

}
