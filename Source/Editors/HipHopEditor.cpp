#include "Editors/HipHopEditor.h"

#include "Editors/HipHopEditorWidget.h"

#include <QFileDialog>
#include <QFileInfo>

#define FILTER "HIP/HOP files (*.hip *.hop);;All files (*.*)"

namespace Slick {

    HipHopEditor::HipHopEditor(QObject* parent) :
        Editor(parent),
        m_file(),
        m_stream()
    {
        setTitle("Untitled.HIP");
        setDirty(true);

        panelLayout().sceneVisible = false;

        connect(this, &HipHopEditor::pathChanged, this, [=](const QString& path)
        {
            setTitle(QFileInfo(path).fileName());
            setTooltip(path);
        });
    }

    EditorWidget* HipHopEditor::createWidget()
    {
        HipHopEditorWidget* widget = new HipHopEditorWidget;
        widget->loadFile(&m_file);

        return widget;
    }

    Editor::OpenResult HipHopEditor::open()
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

        if (!m_stream.Open(m_path.toStdString()))
        {
            return OpenFailed;
        }

        m_file.SetStream(&m_stream);

        if (!m_file.Read())
        {
            return OpenFailed;
        }

        m_stream.Close();

        setDirty(false);

        return OpenSuccessful;
    }

    Editor::SaveResult HipHopEditor::save(bool saveAs)
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

        setDirty(false);

        return SaveSuccessful;
    }

    QString HipHopEditor::getOpenFileName()
    {
        return QFileDialog::getOpenFileName(nullptr, tr("Open HIP/HOP File"), QString(), FILTER);
    }

    QString HipHopEditor::getSaveFileName()
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
                path += ".HIP";
            }
        }

        return QFileDialog::getSaveFileName(nullptr, tr("Save HIP/HOP File"), path, FILTER);
    }

}
