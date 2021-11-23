#include "Editors/SceneEditorViewport.h"

#include <QDateTime>

namespace Slick {

    SceneEditorViewport::SceneEditorViewport(QWindow* parent) :
        Render::Viewport(parent),
        m_scene(nullptr)
    {
    }

    void SceneEditorViewport::update(float dt)
    {
        if (m_scene)
        {
            m_scene->update(dt);
        }
    }

    void SceneEditorViewport::render(Render::Context& context)
    {
        if (m_scene)
        {
            m_scene->render(context);
        }
    }

    void SceneEditorViewport::setScene(Scene* scene)
    {
        m_scene = scene;

        QOpenGLWindow::update();
    }

}
