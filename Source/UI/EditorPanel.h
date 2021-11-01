#pragma once

#include "Editors/IEditor.h"

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

        void addEditor(IEditor* editor);
        void removeEditor(IEditor* editor);
        int editorCount() const;
        IEditor* editor() const;
        IEditor* editor(int index) const;
        QList<IEditor*> editors() const;
        bool openEditor(IEditor* editor);
        bool openEditors(const QList<IEditor*>& editors);
        bool closeEditor();
        bool closeEditor(IEditor* editor);
        bool closeEditors(const QList<IEditor*>& editors);
        bool closeAll();
        bool saveEditor();
        bool saveEditor(IEditor* editor);
        bool saveEditorAs();
        bool saveEditorAs(IEditor* editor);
        bool saveEditors(const QList<IEditor*>& editors);
        bool saveAll();

        virtual bool eventFilter(QObject* o, QEvent* event) override;

    signals:
        void editorChanged(IEditor* editor);

    private:
        EditorPanel(QWidget* parent = nullptr);

        QTabWidget* m_tabWidget;

        bool saveEditors(const QList<IEditor*>& editors, bool saveAs, bool remove);
        QString editorDisplayText(IEditor* editor);
    };

}
