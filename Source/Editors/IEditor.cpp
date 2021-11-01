#include "Editors/IEditor.h"

namespace Slick {

    IEditor::IEditor(QObject* parent) :
        QObject(parent),
        m_widget(nullptr),
        m_title("Untitled"),
        m_dirty(false)
    {
    }

    IEditorWidget* IEditor::widget()
    {
        if (!m_widget)
        {
            m_widget = createWidget();
            m_widget->setEditor(this);
        }

        return m_widget;
    }

    IEditorWidget::IEditorWidget(QWidget* parent) :
        QWidget(parent),
        m_editor(nullptr)
    {
    }

}
