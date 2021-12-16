#include "Editors/SceneEditor.h"

#include "Editors/SceneEditorWidget.h"
#include "UI/OpenSceneDialog.h"
#include "UI/ScenePanel.h"

namespace Slick {

    SceneEditor::SceneEditor(QObject* parent) :
        Editor(parent),
        m_scene(nullptr)
    {
        setTitle("Untitled");
        setDirty(true);
    }

    EditorWidget* SceneEditor::createWidget()
    {
        SceneEditorWidget* widget = new SceneEditorWidget;
        widget->setScene(m_scene);

        return widget;
    }

    Editor::OpenResult SceneEditor::open()
    {
        if (!m_scene)
        {
            OpenSceneDialog dialog;

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

            m_scene = new Scene(this);
            m_scene->setGame(dialog.game());
            m_scene->setPlatform(dialog.platform());
            m_scene->setLanguage(dialog.language());
            m_scene->setRegion(dialog.region());

            for (const QString& path : paths)
            {
                SceneFile* file = new SceneFile(m_scene);
                file->setPath(path);
                m_scene->addFile(file);
            }

            if (!m_scene->load())
            {
                delete m_scene;
                m_scene = nullptr;

                return OpenFailed;
            }

            m_scene->setup();
        }

        setDirty(false);

        return OpenSuccessful;
    }

    Editor::SaveResult SceneEditor::save(bool saveAs)
    {
        setDirty(false);

        return SaveSuccessful;
    }

    void SceneEditor::enter()
    {
        ScenePanel::instance()->setScene(m_scene);
    }

    void SceneEditor::exit()
    {
        ScenePanel::instance()->setScene(nullptr);
    }

}
