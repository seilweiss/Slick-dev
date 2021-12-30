#pragma once

#include "core/editor.h"

#include <QWidget>

class QTabWidget;

namespace Slick {

    namespace Panels {

        class EditorPanel : public QWidget
        {
            Q_OBJECT

        public:
            static EditorPanel* instance()
            {
                static EditorPanel* theInstance = new EditorPanel;
                return theInstance;
            }

            void addEditor(Core::Editor* editor);
            void removeEditor(Core::Editor* editor);
            int editorCount() const;
            Core::Editor* editor() const;
            Core::Editor* editor(int index) const;
            QList<Core::Editor*> editors() const;
            bool openEditor(Core::Editor* editor);
            bool openEditors(const QList<Core::Editor*>& editors);
            bool closeEditor();
            bool closeEditor(Core::Editor* editor);
            bool closeEditors(const QList<Core::Editor*>& editors);
            bool closeAll();
            bool saveEditor();
            bool saveEditor(Core::Editor* editor);
            bool saveEditorAs();
            bool saveEditorAs(Core::Editor* editor);
            bool saveEditors(const QList<Core::Editor*>& editors);
            bool saveAll();

            virtual bool eventFilter(QObject* o, QEvent* event) override;

        signals:
            void editorChanged(Core::Editor* editor);

        private:
            EditorPanel(QWidget* parent = nullptr);

            QTabWidget* m_tabWidget;
            Core::Editor* m_prevEditor;

            bool saveEditors(const QList<Core::Editor*>& editors, bool saveAs, bool remove);
            QString editorDisplayText(Core::Editor* editor);
        };

    }

}
