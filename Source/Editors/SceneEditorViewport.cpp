#include "Editors/SceneEditorViewport.h"

#include <QDateTime>

namespace Slick {

    SceneEditorViewport::SceneEditorViewport(RenderContext* context, QWindow* parent) :
        Viewport(context, parent),
        m_scene(nullptr)
    {
    }

    void SceneEditorViewport::update()
    {
        Viewport::update();

        if (m_scene)
        {
            m_scene->update(context());
        }
    }

    void SceneEditorViewport::render()
    {
        Viewport::render();

        if (m_scene)
        {
            m_scene->render(context());
        }

        emit doneRendering();
    }

    void SceneEditorViewport::setScene(Scene* scene)
    {
        m_scene = scene;

        QOpenGLWindow::update();
    }

}
