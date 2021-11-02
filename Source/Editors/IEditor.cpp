#include "Editors/IEditor.h"

namespace Slick {

    IEditor::IEditor(QObject* parent) :
        QObject(parent),
        m_widget(nullptr),
        m_title("Untitled"),
        m_dirty(false)
    {
        m_panelLayout.projectVisible = true;
        m_panelLayout.sceneVisible = true;
        m_panelLayout.inspectorVisible = true;
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
