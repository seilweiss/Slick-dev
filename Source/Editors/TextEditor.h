#pragma once

#include "Editors/IEditor.h"

class QTextEdit;

namespace Slick {

    class TextEditorWidget;

    class TextEditor : public IEditor
    {
        Q_OBJECT
        Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

    public:
        TextEditor(QObject* parent = nullptr);

        virtual IEditorWidget* createWidget() override;
        virtual SaveResult save() override;
        virtual SaveResult saveAs() override;
        virtual OpenResult open() override;

        QString path() const { return m_path; }
        void setPath(const QString& path) { m_path = path; emit pathChanged(path); }

        static QString filter();
        static QString getOpenFileName();
        static QString getSaveFileName(TextEditor* editor = nullptr);

    signals:
        void pathChanged(const QString& path);

    private:
        QString m_path;
        TextEditorWidget* m_widget;
        QString m_readText;
    };

    class TextEditorWidget : public IEditorWidget
    {
        Q_OBJECT
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

    public:
        TextEditorWidget(QWidget* parent = nullptr);

        QString text() const;
        void setText(const QString& text);

    signals:
        void textChanged(const QString& text);

    private:
        QTextEdit* m_textEdit;
    };

}
