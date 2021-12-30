#include "editors/texteditorwidget.h"

#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QFontDatabase>

namespace Slick {

    namespace Editors {

        TextEditorWidget::TextEditorWidget(QWidget* parent) :
            EditorWidget(parent),
            m_textEdit(new QPlainTextEdit)
        {
            m_textEdit->setTabChangesFocus(false);
            m_textEdit->setUndoRedoEnabled(true);
            m_textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
            m_textEdit->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
            m_textEdit->clear();

            connect(m_textEdit, &QPlainTextEdit::textChanged, this, [=]
            {
                emit textChanged(m_textEdit->toPlainText());
            });

            QHBoxLayout* mainLayout = new QHBoxLayout;

            mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->addWidget(m_textEdit, 1);

            setLayout(mainLayout);
        }

        QString TextEditorWidget::text() const
        {
            return m_textEdit->toPlainText();
        }

        void TextEditorWidget::setText(const QString& text)
        {
            m_textEdit->setPlainText(text);

            emit textChanged(text);
        }

    }

}
