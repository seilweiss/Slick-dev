#include "Editors/TextEditor.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QFontDatabase>
#include <QTextStream>

namespace Slick {

    TextEditor::TextEditor(QObject* parent) :
        IEditor(parent),
        m_path(),
        m_widget(nullptr),
        m_readText()
    {
        setTitle("Untitled.txt");
        setDirty(true);

        panelLayout().sceneVisible = false;

        connect(this, &TextEditor::pathChanged, this, [=](const QString& path)
        {
            setTitle(QFileInfo(path).fileName());
            setTooltip(path);
        });
    }

    IEditorWidget* TextEditor::createWidget()
    {
        m_widget = new TextEditorWidget;
        m_widget->setText(m_readText);

        connect(m_widget, &TextEditorWidget::textChanged, this, [=]
        {
            setDirty(true);
        });

        return m_widget;
    }

    IEditor::SaveResult TextEditor::save()
    {
        if (m_path.isEmpty())
        {
            return saveAs();
        }

        setDirty(false);

        return SaveSuccessful;
    }

    IEditor::SaveResult TextEditor::saveAs()
    {
        QString path = getSaveFileName(this);

        if (path.isEmpty())
        {
            return SaveCancelled;
        }

        setPath(path);
        setDirty(false);

        return SaveSuccessful;
    }

    IEditor::OpenResult TextEditor::open()
    {
        if (m_path.isEmpty())
        {
            QString path = getOpenFileName();

            if (path.isEmpty())
            {
                return OpenCancelled;
            }

            m_path = path;
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

    QString TextEditor::filter()
    {
        return "Text files (*.txt *.ini *.lip *.lop);;All files (*.*)";
    }

    QString TextEditor::getOpenFileName()
    {
        return QFileDialog::getOpenFileName(nullptr, tr("Open Text File"), QString(), filter());
    }

    QString TextEditor::getSaveFileName(TextEditor* editor)
    {
        QString path;

        if (editor)
        {
            if (!editor->path().isEmpty())
            {
                path = editor->path();
            }
            else
            {
                path = editor->title();

                if (QFileInfo(path).suffix().isEmpty())
                {
                    path += ".txt";
                }
            }
        }

        return QFileDialog::getSaveFileName(nullptr, tr("Save Text File"), path, filter());
    }

    TextEditorWidget::TextEditorWidget(QWidget* parent) :
        IEditorWidget(parent),
        m_textEdit(new QTextEdit)
    {
        m_textEdit->setAcceptRichText(false);
        m_textEdit->setAutoFormatting(QTextEdit::AutoNone);
        m_textEdit->setTabChangesFocus(false);
        m_textEdit->setUndoRedoEnabled(true);
        m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
        m_textEdit->setCurrentFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
        m_textEdit->setFontPointSize(12);
        m_textEdit->clear();

        QHBoxLayout* mainLayout = new QHBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addWidget(m_textEdit, 1);

        setLayout(mainLayout);
    }

    QString TextEditorWidget::text() const
    {
        return m_textEdit->toPlainText();
    }

    void TextEditorWidget::setText(const QString &text)
    {
        m_textEdit->setPlainText(text);

        emit textChanged(text);
    }

}
