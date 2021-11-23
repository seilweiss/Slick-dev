#include "Core/Editor.h"

namespace Slick {

    Editor::Editor(QObject* parent) :
        QObject(parent),
        m_widget(nullptr),
        m_title("Untitled"),
        m_dirty(false)
    {
        m_panelLayout.projectVisible = true;
        m_panelLayout.sceneVisible = true;
        m_panelLayout.inspectorVisible = true;
    }

    Editor::~Editor()
    {
        if (m_widget)
        {
            m_widget->deleteLater();
        }
    }

    EditorWidget* Editor::widget()
    {
        if (!m_widget)
        {
            m_widget = createWidget();
            m_widget->setEditor(this);
        }

        return m_widget;
    }

}
