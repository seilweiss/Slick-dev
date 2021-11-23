#pragma once

#include "Core/EditorWidget.h"
#include "Core/Scene.h"

namespace Slick {

    class SceneEditorViewport;

    class SceneEditorWidget : public EditorWidget
    {
        Q_OBJECT

    public:
        SceneEditorWidget(QWidget* parent = nullptr);

        bool loadScene(Scene* scene);

    private:
        Scene* m_scene;
        SceneEditorViewport* m_viewport;
    };

}
