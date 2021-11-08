#include "Editors/SceneEditor.h"

#include "UI/OpenSceneDialog.h"

#include <QHBoxLayout>

namespace Slick {

    SceneEditor::SceneEditor(QObject* parent) :
        IEditor(parent)
    {
        setTitle("Untitled");
        setDirty(true);
    }

    IEditorWidget* SceneEditor::createWidget()
    {
        m_widget = new SceneEditorWidget(this);

        return m_widget;
    }

    IEditor::SaveResult SceneEditor::save()
    {
        setDirty(false);

        return SaveSuccessful;
    }

    IEditor::SaveResult SceneEditor::saveAs()
    {
        setDirty(false);

        return SaveSuccessful;
    }

    IEditor::OpenResult SceneEditor::open()
    {
        OpenSceneDialog dialog;

        if (dialog.exec() != QDialog::Accepted)
        {
            return OpenCancelled;
        }

        setTitle(dialog.sceneName());

        {
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
        }

        setDirty(false);

        return OpenSuccessful;
    }

    SceneEditorWidget::SceneEditorWidget(SceneEditor* editor, QWidget* parent) :
        IEditorWidget(parent),
        m_editor(editor)
    {
        QHBoxLayout* mainLayout = new QHBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);

        setLayout(mainLayout);
    }

}
