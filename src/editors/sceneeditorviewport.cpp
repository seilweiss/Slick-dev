#include "editors/sceneeditorviewport.h"

namespace Slick {

    namespace Editors {

        SceneEditorViewport::SceneEditorViewport(QWindow* parent) :
            Viewport(parent),
            m_scene(nullptr)
        {
        }

        void SceneEditorViewport::update()
        {
            Viewport::update();

            if (m_scene)
            {
                m_scene->update();
            }
        }

        void SceneEditorViewport::render()
        {
            Viewport::render();

            if (m_scene)
            {
                m_scene->render();
            }

            emit doneRendering();
        }

        void SceneEditorViewport::setScene(Core::Scene* scene)
        {
            if (m_scene)
            {
                m_scene->disconnect(this);
            }

            m_scene = scene;

            setContext(m_scene->renderContext());

            QOpenGLWindow::update();
        }

    }

}
