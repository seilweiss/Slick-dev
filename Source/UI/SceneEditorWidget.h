#pragma once

#include "UI/IEditorWidget.h"
#include "Core/Scene.h"

namespace Slick {

    class SceneEditorWidget : public IEditorWidget
    {
        Q_OBJECT

    public:
        SceneEditorWidget(QWidget* parent = nullptr);

        bool loadScene(Scene* scene);

    private:
        Scene* m_scene;
    };

}
