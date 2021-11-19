#include "UI/SceneEditorWidget.h"

#include <QHBoxLayout>

namespace Slick {

    SceneEditorWidget::SceneEditorWidget(QWidget* parent) :
        IEditorWidget(parent),
        m_scene(nullptr)
    {
        QHBoxLayout* mainLayout = new QHBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);

        setLayout(mainLayout);
    }

    bool SceneEditorWidget::loadScene(Scene* scene)
    {
        m_scene = scene;

        return true;
    }

}
