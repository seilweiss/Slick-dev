#include "editors/sceneeditor.h"

#include "editors/sceneeditorwidget.h"
#include "dialogs/openscene.h"
#include "panels/scenepanel.h"

namespace Slick {

    namespace Editors {

        SceneEditor::SceneEditor(QObject* parent) :
            Editor(parent),
            m_scene(nullptr)
        {
            setTitle("Untitled");
            setDirty(true);
        }

        Core::EditorWidget* SceneEditor::createWidget()
        {
            SceneEditorWidget* widget = new SceneEditorWidget;
            widget->setScene(m_scene);

            return widget;
        }

        Core::Editor::OpenResult SceneEditor::open()
        {
            if (!m_scene)
            {
                Dialogs::OpenScene dialog;

                if (dialog.exec() != QDialog::Accepted)
                {
                    return OpenCancelled;
                }

                setTitle(dialog.sceneName());

                QStringList paths;

                if (!dialog.hipPath().isEmpty())
                {
                    paths.append(dialog.hipPath());
                }

                if (!dialog.hopPath().isEmpty())
                {
                    paths.append(dialog.hopPath());
                }

                paths.append(dialog.locHipPaths());

                setTooltip(paths.join("\n"));

                m_scene = new Core::Scene(this);
                m_scene->setGame(dialog.game());
                m_scene->setPlatform(dialog.platform());
                m_scene->setLanguage(dialog.language());
                m_scene->setRegion(dialog.region());

                for (const QString& path : paths)
                {
                    Core::SceneFile* file = new Core::SceneFile(m_scene);
                    file->setPath(path);
                    m_scene->addFile(file);
                }

                if (!m_scene->load())
                {
                    delete m_scene;
                    m_scene = nullptr;

                    return OpenFailed;
                }

                connect(m_scene->renderContext(), &Render::Context::initialized, m_scene, &Core::Scene::setup);
            }

            setDirty(false);

            return OpenSuccessful;
        }

        Core::Editor::SaveResult SceneEditor::save(bool saveAs)
        {
            setDirty(false);

            return SaveSuccessful;
        }

        void SceneEditor::enter()
        {
            Panels::ScenePanel::instance()->setScene(m_scene);
        }

        void SceneEditor::exit()
        {
            Panels::ScenePanel::instance()->setScene(nullptr);
        }

    }

}
