#include "panels/editorpanel.h"

#include "dialogs/editorlist.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>
#include <QMessageBox>
#include <QEvent>
#include <QMouseEvent>

namespace Slick {

    namespace Panels {

        EditorPanel::EditorPanel(QWidget* parent) :
            QWidget(parent),
            m_tabWidget(new QTabWidget),
            m_prevEditor(nullptr)
        {
            m_tabWidget->setTabsClosable(true);
            m_tabWidget->setMovable(true);
            m_tabWidget->setUsesScrollButtons(true);
            //m_tabWidget->setDocumentMode(true);
            m_tabWidget->tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
            m_tabWidget->tabBar()->installEventFilter(this);

            connect(m_tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index)
            {
                closeEditor(editor(index));
            });

            connect(m_tabWidget, &QTabWidget::currentChanged, this, [=](int index)
            {
                Core::Editor* newEditor = editor(index);

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

        void EditorPanel::addEditor(Core::Editor* editor)
        {
            editor->setParent(this);

            int index = m_tabWidget->addTab(editor->widget(), editorDisplayText(editor));

            m_tabWidget->setTabToolTip(index, editor->tooltip());

            connect(editor, &Core::Editor::titleChanged, this, [=]
            {
                m_tabWidget->setTabText(m_tabWidget->indexOf(editor->widget()), editorDisplayText(editor));
            });

            connect(editor, &Core::Editor::tooltipChanged, this, [=](const QString& tooltip)
            {
                m_tabWidget->setTabToolTip(m_tabWidget->indexOf(editor->widget()), tooltip);
            });

            connect(editor, &Core::Editor::dirtyChanged, this, [=]
            {
                m_tabWidget->setTabText(m_tabWidget->indexOf(editor->widget()), editorDisplayText(editor));
            });

            m_tabWidget->setCurrentIndex(index);
        }

        void EditorPanel::removeEditor(Core::Editor* editor)
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

        Core::Editor* EditorPanel::editor() const
        {
            int index = m_tabWidget->currentIndex();
            return index != -1 ? editor(index) : nullptr;
        }

        Core::Editor* EditorPanel::editor(int index) const
        {
            return index != -1 ? ((Core::EditorWidget*)m_tabWidget->widget(index))->editor() : nullptr;
        }

        QList<Core::Editor*> EditorPanel::editors() const
        {
            QList<Core::Editor*> editors;
            int count = editorCount();

            for (int i = 0; i < count; i++)
            {
                editors.append(editor(i));
            }

            return editors;
        }

        bool EditorPanel::openEditor(Core::Editor *editor)
        {
            return openEditors({ editor });
        }

        bool EditorPanel::openEditors(const QList<Core::Editor*>& editors)
        {
            bool success = true;
            QList<Core::Editor*> failedEditors;

            for (Core::Editor* editor : editors)
            {
                bool cancel = false;
                Core::Editor::OpenResult openResult = editor->open();

                switch (openResult)
                {
                case Core::Editor::OpenSuccessful:
                    addEditor(editor);
                    break;
                case Core::Editor::OpenFailed:
                    failedEditors.append(editor);
                    success = false;
                    break;
                case Core::Editor::OpenCancelled:
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
                Dialogs::EditorList::openFailed(this, failedEditors);
            }

            return success;
        }

        bool EditorPanel::closeEditor()
        {
            Core::Editor* e = editor();
            return e ? closeEditor(e) : false;
        }

        bool EditorPanel::closeEditor(Core::Editor* editor)
        {
            return closeEditors({ editor });
        }

        bool EditorPanel::closeEditors(const QList<Core::Editor*>& editors)
        {
            bool success = true;
            QList<Core::Editor*> dirtyEditors;

            for (Core::Editor* editor : editors)
            {
                if (editor->dirty())
                {
                    dirtyEditors.append(editor);
                }
            }

            if (dirtyEditors.empty())
            {
                for (Core::Editor* editor : editors)
                {
                    removeEditor(editor);
                }
            }
            else
            {
                Dialogs::EditorList::Result askSaveResult = Dialogs::EditorList::askSave(this, dirtyEditors);

                switch (askSaveResult)
                {
                case Dialogs::EditorList::OK: // not an option
                {
                    break;
                }
                case Dialogs::EditorList::Save:
                {
                    success = saveEditors(dirtyEditors, false, true);
                    break;
                }
                case Dialogs::EditorList::DontSave:
                {
                    for (Core::Editor* editor : editors)
                    {
                        removeEditor(editor);
                    }

                    break;
                }
                case Dialogs::EditorList::Cancel:
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
            Core::Editor* e = editor();
            return e ? saveEditor(e) : false;
        }

        bool EditorPanel::saveEditor(Core::Editor* editor)
        {
            return saveEditors({ editor }, false, false);
        }

        bool EditorPanel::saveEditorAs()
        {
            Core::Editor* e = editor();
            return e ? saveEditorAs(e) : false;
        }

        bool EditorPanel::saveEditorAs(Core::Editor* editor)
        {
            return saveEditors({ editor }, true, false);
        }

        bool EditorPanel::saveEditors(const QList<Core::Editor*>& editors)
        {
            return saveEditors(editors, false, false);
        }

        bool EditorPanel::saveAll()
        {
            return saveEditors(editors(), false, false);
        }

        bool EditorPanel::saveEditors(const QList<Core::Editor*>& editors, bool saveAs, bool remove)
        {
            bool success = true;
            QList<Core::Editor*> failedEditors;

            for (Core::Editor* editor : editors)
            {
                bool cancel = false;

                if (editor->dirty() || saveAs)
                {
                    Core::Editor::SaveResult saveResult = editor->save(saveAs);

                    switch (saveResult)
                    {
                    case Core::Editor::SaveSuccessful:
                        if (remove)
                        {
                            removeEditor(editor);
                        }
                        break;
                    case Core::Editor::SaveFailed:
                        failedEditors.append(editor);
                        success = false;
                        break;
                    case Core::Editor::SaveCancelled:
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
                Dialogs::EditorList::saveFailed(this, failedEditors);
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

        QString EditorPanel::editorDisplayText(Core::Editor* editor)
        {
            QString text = editor->title();

            if (editor->dirty())
            {
                text += "*";
            }

            return text;
        }

    }

}
