#include "editors/texteditor.h"

#include "editors/texteditorwidget.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>

#define FILTER "Text files (*.txt *.ini *.lip *.lop);;All files (*.*)"

namespace Slick {

    namespace Editors {

        TextEditor::TextEditor(QObject* parent) :
            Editor(parent),
            m_path(),
            m_readText()
        {
            setTitle("Untitled.txt");
            setDirty(true);

            connect(this, &TextEditor::pathChanged, this, [=](const QString& path)
            {
                setTitle(QFileInfo(path).fileName());
                setTooltip(path);
            });
        }

        Core::EditorWidget* TextEditor::createWidget()
        {
            TextEditorWidget* widget = new TextEditorWidget;
            widget->setText(m_readText);

            connect(widget, &TextEditorWidget::textChanged, this, [=]
            {
                setDirty(true);
            });

            return widget;
        }

        Core::Editor::OpenResult TextEditor::open()
        {
            if (m_path.isEmpty())
            {
                QString path = getOpenFileName();

                if (path.isEmpty())
                {
                    return OpenCancelled;
                }

                setPath(path);
            }

            QFile file(m_path);

            if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                return OpenFailed;
            }

            QTextStream stream(&file);

            m_readText = stream.readAll();

            setDirty(false);

            return OpenSuccessful;
        }

        Core::Editor::SaveResult TextEditor::save(bool saveAs)
        {
            if (saveAs || m_path.isEmpty())
            {
                QString path = getSaveFileName();

                if (path.isEmpty())
                {
                    return SaveCancelled;
                }

                setPath(path);
            }

            QFile file(m_path);

            if (!file.open(QFile::WriteOnly | QFile::Text))
            {
                return SaveFailed;
            }

            QTextStream stream(&file);
            TextEditorWidget* w = (TextEditorWidget*)widget();

            stream << w->text();

            setDirty(false);

            return SaveSuccessful;
        }

        QString TextEditor::getOpenFileName()
        {
            return QFileDialog::getOpenFileName(nullptr, tr("Open Text File"), QString(), FILTER);
        }

        QString TextEditor::getSaveFileName()
        {
            QString path;

            if (!m_path.isEmpty())
            {
                path = m_path;
            }
            else
            {
                path = title();

                if (QFileInfo(path).suffix().isEmpty())
                {
                    path += ".txt";
                }
            }

            return QFileDialog::getSaveFileName(nullptr, tr("Save Text File"), path, FILTER);
        }

    }

}
