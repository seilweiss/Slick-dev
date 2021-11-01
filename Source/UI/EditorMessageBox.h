#pragma once

#include <QDialog>
#include <QStyle>

#include <Editors/IEditor.h>

class QListWidget;
class QLabel;
class QDialogButtonBox;

namespace Slick {

    class EditorMessageBox : public QDialog
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

        static Result askSave(QWidget* parent, const QList<IEditor*>& editors);
        static Result openFailed(QWidget* parent, const QList<IEditor*>& editors);
        static Result saveFailed(QWidget* parent, const QList<IEditor*>& editors);

    private:
        EditorMessageBox(QWidget* parent, const QList<IEditor*>& editors, const QString& title, const QString& text, QStyle::StandardPixmap icon);

        QListWidget* m_listWidget;
        QDialogButtonBox* m_buttonBox;
        Result m_result;

        void addButton(Result result);
    };

}
