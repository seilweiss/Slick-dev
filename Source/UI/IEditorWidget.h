#pragma once

#include <QWidget>

Q_MOC_INCLUDE("Editors/IEditor.h")

namespace Slick {

    class IEditor;

    class IEditorWidget : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(IEditor* editor READ editor WRITE setEditor)

    public:
        IEditorWidget(QWidget* parent = nullptr);

        IEditor* editor() const { return m_editor; }
        void setEditor(IEditor* editor) { m_editor = editor; }

    private:
        IEditor* m_editor;
    };

}
