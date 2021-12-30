#include "dialogs/editorlist.h"

#include <QListWidget>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Slick {

    namespace Dialogs {

        EditorList::EditorList(QWidget* parent, const QList<Core::Editor*>& editors, const QString& title, const QString& text, QStyle::StandardPixmap icon) :
            QDialog(parent),
            m_listWidget(new QListWidget),
            m_buttonBox(new QDialogButtonBox(Qt::Horizontal))
        {
            setWindowTitle(title);
            setWindowFlag(Qt::WindowContextHelpButtonHint, false);

            m_listWidget->setFocusPolicy(Qt::NoFocus);
            m_listWidget->setSelectionMode(QListWidget::NoSelection);

            for (Core::Editor* editor : editors)
            {
                m_listWidget->addItem(editor->title());
            }

            QLabel* textLabel = new QLabel(text);

            QLabel* iconLabel = new QLabel;
            iconLabel->setPixmap(style()->standardIcon(icon).pixmap(64, 64));

            QHBoxLayout* mainLayout = new QHBoxLayout;
            QVBoxLayout* vbox = new QVBoxLayout;

            vbox->addWidget(textLabel);
            vbox->addWidget(m_listWidget);
            vbox->addWidget(m_buttonBox);

            mainLayout->addWidget(iconLabel, 0, Qt::AlignTop);
            mainLayout->addLayout(vbox, 1);

            setLayout(mainLayout);
        }

        EditorList::Result EditorList::askSave(QWidget* parent, const QList<Core::Editor*>& editors)
        {
            EditorList dialog(parent, editors, tr("Save Changes"), tr("Save changes to the following items?"), QStyle::SP_MessageBoxQuestion);

            dialog.addButton(Save);
            dialog.addButton(DontSave);
            dialog.addButton(Cancel);
            dialog.exec();

            return dialog.m_result;
        }

        EditorList::Result EditorList::openFailed(QWidget* parent, const QList<Core::Editor*>& editors)
        {
            EditorList dialog(parent, editors, tr("Open Failed"), tr("The following items could not be opened:"), QStyle::SP_MessageBoxCritical);

            dialog.addButton(OK);
            dialog.exec();

            return dialog.m_result;
        }

        EditorList::Result EditorList::saveFailed(QWidget* parent, const QList<Core::Editor*>& editors)
        {
            EditorList dialog(parent, editors, tr("Save Failed"), tr("The following items could not be saved:"), QStyle::SP_MessageBoxCritical);

            dialog.addButton(OK);
            dialog.exec();

            return dialog.m_result;
        }

        void EditorList::addButton(EditorList::Result result)
        {
            QString text;
            QDialogButtonBox::ButtonRole role;

            switch (result)
            {
            case OK:
                text = tr("OK");
                role = QDialogButtonBox::AcceptRole;
                break;
            case Save:
                text = tr("Save");
                role = QDialogButtonBox::AcceptRole;
                break;
            case DontSave:
                text = tr("Don't Save");
                role = QDialogButtonBox::DestructiveRole;
                break;
            case Cancel:
                text = tr("Cancel");
                role = QDialogButtonBox::RejectRole;
                break;
            }

            QPushButton* button = m_buttonBox->addButton(text, role);

            connect(button, &QPushButton::clicked, this, [=]
            {
                m_result = result;

                if (result == Cancel)
                {
                    reject();
                }
                else
                {
                    accept();
                }
            });
        }

    }

}
