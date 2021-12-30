#pragma once

#include <QWidget>

Q_MOC_INCLUDE("core/editor.h")

namespace Slick {

    namespace Core {

        class Editor;

        class EditorWidget : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(Editor* editor READ editor WRITE setEditor)

        public:
            EditorWidget(QWidget* parent = nullptr);

            Editor* editor() const { return m_editor; }
            void setEditor(Editor* editor) { m_editor = editor; }

        private:
            Editor* m_editor;
        };

    }

}
