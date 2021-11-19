#include "UI/EditorPanel.h"

#include "UI/EditorMessageBox.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>
#include <QMessageBox>
#include <QEvent>
#include <QMouseEvent>

namespace Slick {

    EditorPanel::EditorPanel(QWidget* parent) :
        QWidget(parent),
        m_tabWidget(new QTabWidget),
        m_prevEditor(nullptr)
    {
        m_tabWidget->setTabsClosable(true);
        m_tabWidget->setMovable(true);
        m_tabWidget->setUsesScrollButtons(true);
        m_tabWidget->setDocumentMode(true);
        m_tabWidget->tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
        m_tabWidget->tabBar()->installEventFilter(this);

        connect(m_tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index)
        {
            closeEditor(editor(index));
        });

        connect(m_tabWidget, &QTabWidget::currentChanged, this, [=](int index)
        {
            IEditor* newEditor = editor(index);

            if (m_prevEditor)
            {
                m_prevEditor->exit();
            }

            if (newEditor)
            {
                newEditor->enter();
            }

            m_prevEditor = newEditor;

            emit editorChanged(newEditor);
        });

        QVBoxLayout* mainLayout = new QVBoxLayout;

        mainLayout->addWidget(m_tabWidget, 1);

        setLayout(mainLayout);
    }

    void EditorPanel::addEditor(IEditor* editor)
    {
        editor->setParent(this);

        int index = m_tabWidget->addTab(editor->widget(), editorDisplayText(editor));

        m_tabWidget->setTabToolTip(index, editor->tooltip());

        connect(editor, &IEditor::titleChanged, this, [=]
        {
            m_tabWidget->setTabText(m_tabWidget->indexOf(editor->widget()), editorDisplayText(editor));
        });

        connect(editor, &IEditor::tooltipChanged, this, [=](const QString& tooltip)
        {
            m_tabWidget->setTabToolTip(m_tabWidget->indexOf(editor->widget()), tooltip);
        });

        connect(editor, &IEditor::dirtyChanged, this, [=]
        {
            m_tabWidget->setTabText(m_tabWidget->indexOf(editor->widget()), editorDisplayText(editor));
        });

        m_tabWidget->setCurrentIndex(index);
    }

    void EditorPanel::removeEditor(IEditor* editor)
    {
        int index = m_tabWidget->indexOf(editor->widget());

        if (index == m_tabWidget->currentIndex())
        {
            editor->exit();
            m_prevEditor = nullptr;
        }

        m_tabWidget->removeTab(index);

        //editor->setParent(nullptr);
        //editor->disconnect(this);
        editor->deleteLater();
    }

    int EditorPanel::editorCount() const
    {
        return m_tabWidget->count();
    }

    IEditor* EditorPanel::editor() const
    {
        int index = m_tabWidget->currentIndex();
        return index != -1 ? editor(index) : nullptr;
    }

    IEditor* EditorPanel::editor(int index) const
    {
        return index != -1 ? ((IEditorWidget*)m_tabWidget->widget(index))->editor() : nullptr;
    }

    QList<IEditor*> EditorPanel::editors() const
    {
        QList<IEditor*> editors;
        int count = editorCount();

        for (int i = 0; i < count; i++)
        {
            editors.append(editor(i));
        }

        return editors;
    }

    bool EditorPanel::openEditor(IEditor *editor)
    {
        return openEditors({ editor });
    }

    bool EditorPanel::openEditors(const QList<IEditor*>& editors)
    {
        bool success = true;
        QList<IEditor*> failedEditors;

        for (IEditor* editor : editors)
        {
            bool cancel = false;
            IEditor::OpenResult openResult = editor->open();

            switch (openResult)
            {
            case IEditor::OpenSuccessful:
                addEditor(editor);
                break;
            case IEditor::OpenFailed:
                failedEditors.append(editor);
                success = false;
                break;
            case IEditor::OpenCancelled:
                success = false;
                cancel = true;
                break;
            }

            if (cancel)
            {
                break;
            }
        }

        if (!failedEditors.empty())
        {
            EditorMessageBox::openFailed(this, failedEditors);
        }

        return success;
    }

    bool EditorPanel::closeEditor()
    {
        IEditor* e = editor();
        return e ? closeEditor(e) : false;
    }

    bool EditorPanel::closeEditor(IEditor* editor)
    {
        return closeEditors({ editor });
    }

    bool EditorPanel::closeEditors(const QList<IEditor*>& editors)
    {
        bool success = true;
        QList<IEditor*> dirtyEditors;

        for (IEditor* editor : editors)
        {
            if (editor->dirty())
            {
                dirtyEditors.append(editor);
            }
        }

        if (dirtyEditors.empty())
        {
            for (IEditor* editor : editors)
            {
                removeEditor(editor);
            }
        }
        else
        {
            EditorMessageBox::Result askSaveResult = EditorMessageBox::askSave(this, dirtyEditors);

            switch (askSaveResult)
            {
            case EditorMessageBox::OK: // not an option
            {
                break;
            }
            case EditorMessageBox::Save:
            {
                success = saveEditors(dirtyEditors, false, true);
                break;
            }
            case EditorMessageBox::DontSave:
            {
                for (IEditor* editor : editors)
                {
                    removeEditor(editor);
                }

                break;
            }
            case EditorMessageBox::Cancel:
            {
                success = false;
                break;
            }
            }
        }

        return success;
    }

    bool EditorPanel::closeAll()
    {
        return closeEditors(editors());
    }

    bool EditorPanel::saveEditor()
    {
        IEditor* e = editor();
        return e ? saveEditor(e) : false;
    }

    bool EditorPanel::saveEditor(IEditor* editor)
    {
        return saveEditors({ editor }, false, false);
    }

    bool EditorPanel::saveEditorAs()
    {
        IEditor* e = editor();
        return e ? saveEditorAs(e) : false;
    }

    bool EditorPanel::saveEditorAs(IEditor* editor)
    {
        return saveEditors({ editor }, true, false);
    }

    bool EditorPanel::saveEditors(const QList<IEditor*>& editors)
    {
        return saveEditors(editors, false, false);
    }

    bool EditorPanel::saveAll()
    {
        return saveEditors(editors(), false, false);
    }

    bool EditorPanel::saveEditors(const QList<IEditor*>& editors, bool saveAs, bool remove)
    {
        bool success = true;
        QList<IEditor*> failedEditors;

        for (IEditor* editor : editors)
        {
            bool cancel = false;

            if (editor->dirty() || saveAs)
            {
                IEditor::SaveResult saveResult = editor->save(saveAs);

                switch (saveResult)
                {
                case IEditor::SaveSuccessful:
                    if (remove)
                    {
                        removeEditor(editor);
                    }
                    break;
                case IEditor::SaveFailed:
                    failedEditors.append(editor);
                    success = false;
                    break;
                case IEditor::SaveCancelled:
                    success = false;
                    cancel = true;
                    break;
                }
            }
            else if (remove)
            {
                removeEditor(editor);
            }

            if (cancel)
            {
                break;
            }
        }

        if (!failedEditors.empty())
        {
            EditorMessageBox::saveFailed(this, failedEditors);
        }

        return success;
    }

    bool EditorPanel::eventFilter(QObject *o, QEvent *event)
    {
        if (o == m_tabWidget->tabBar())
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                QMouseEvent* mouseEvent = (QMouseEvent*)event;

                if (mouseEvent->button() == Qt::MiddleButton)
                {
                    int index = m_tabWidget->tabBar()->tabAt(mouseEvent->pos());

                    if (index != -1)
                    {
                        closeEditor(editor(index));
                        return true;
                    }
                }
            }
        }

        return QWidget::eventFilter(o, event);
    }

    QString EditorPanel::editorDisplayText(IEditor* editor)
    {
        QString text = editor->title();

        if (editor->dirty())
        {
            text += "*";
        }

        return text;
    }

}
