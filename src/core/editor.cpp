#include "core/editor.h"

namespace Slick {

    namespace Core {

        Editor::Editor(QObject* parent) :
            QObject(parent),
            m_widget(nullptr),
            m_title("Untitled"),
            m_dirty(false)
        {
        }

        Editor::~Editor()
        {
            if (m_widget)
            {
                delete m_widget;
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

}
