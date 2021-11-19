#pragma once

#include "UI/IEditorWidget.h"

class QPlainTextEdit;

namespace Slick {

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
        QPlainTextEdit* m_textEdit;
    };

}
