#pragma once

#include "Core/EditorWidget.h"
#include "Core/Scene.h"

class QLabel;

namespace Slick {

    class SceneEditorViewport;

    class SceneEditorWidget : public EditorWidget
    {
        Q_OBJECT

    public:
        SceneEditorWidget(QWidget* parent = nullptr);

        void setScene(Scene* scene);

        RenderContext* context() const { return m_context; }
        SceneEditorViewport* viewport() const { return m_viewport; }

    private:
        Scene* m_scene;
        RenderContext* m_context;
        SceneEditorViewport* m_viewport;
        QLabel* m_statsLabel;

        void updateStats();
    };

}
