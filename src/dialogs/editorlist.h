#pragma once

#include "core/editor.h"

#include <QDialog>
#include <QStyle>

class QListWidget;
class QLabel;
class QDialogButtonBox;

namespace Slick {

    namespace Dialogs {

        class EditorList : public QDialog
        {
            Q_OBJECT

        public:
            enum Result
            {
                OK,
                Save,
                DontSave,
                Cancel
            };

            static Result askSave(QWidget* parent, const QList<Core::Editor*>& editors);
            static Result openFailed(QWidget* parent, const QList<Core::Editor*>& editors);
            static Result saveFailed(QWidget* parent, const QList<Core::Editor*>& editors);

            EditorList(QWidget* parent, const QList<Core::Editor*>& editors, const QString& title, const QString& text, QStyle::StandardPixmap icon);

        private:
            QListWidget* m_listWidget;
            QDialogButtonBox* m_buttonBox;
            Result m_result;

            void addButton(Result result);
        };

    }

}
