#pragma once

#include "Core/Editor.h"

#include <QWidget>

class QTabWidget;

namespace Slick {

    class EditorPanel : public QWidget
    {
        Q_OBJECT

    public:
        static EditorPanel* instance()
        {
            static EditorPanel* theInstance = new EditorPanel;
            return theInstance;
        }

        void addEditor(Editor* editor);
        void removeEditor(Editor* editor);
        int editorCount() const;
        Editor* editor() const;
        Editor* editor(int index) const;
        QList<Editor*> editors() const;
        bool openEditor(Editor* editor);
        bool openEditors(const QList<Editor*>& editors);
        bool closeEditor();
        bool closeEditor(Editor* editor);
        bool closeEditors(const QList<Editor*>& editors);
        bool closeAll();
        bool saveEditor();
        bool saveEditor(Editor* editor);
        bool saveEditorAs();
        bool saveEditorAs(Editor* editor);
        bool saveEditors(const QList<Editor*>& editors);
        bool saveAll();

        virtual bool eventFilter(QObject* o, QEvent* event) override;

    signals:
        void editorChanged(Editor* editor);

    private:
        EditorPanel(QWidget* parent = nullptr);

        QTabWidget* m_tabWidget;
        Editor* m_prevEditor;

        bool saveEditors(const QList<Editor*>& editors, bool saveAs, bool remove);
        QString editorDisplayText(Editor* editor);
    };

}
