#include "Editors/SceneEditor.h"

#include "UI/SceneEditorWidget.h"
#include "UI/OpenSceneDialog.h"
#include "UI/ScenePanel.h"

namespace Slick {

    SceneEditor::SceneEditor(QObject* parent) :
        IEditor(parent),
        m_scene(nullptr)
    {
        setTitle("Untitled");
        setDirty(true);
    }

    IEditorWidget* SceneEditor::createWidget()
    {
        SceneEditorWidget* widget = new SceneEditorWidget;
        widget->loadScene(m_scene);

        return widget;
    }

    IEditor::OpenResult SceneEditor::open()
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
                SceneFile* file = new SceneFile;
                file->setPath(path);
                m_scene->addFile(file);
            }

            if (!m_scene->load())
            {
                delete m_scene;
                m_scene = nullptr;

                return OpenFailed;
            }
        }

        setDirty(false);

        return OpenSuccessful;
    }

    IEditor::SaveResult SceneEditor::save(bool saveAs)
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
