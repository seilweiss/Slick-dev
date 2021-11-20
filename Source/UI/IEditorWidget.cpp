#include "UI/IEditorWidget.h"

namespace Slick {

    IEditorWidget::IEditorWidget(QWidget* parent) :
        QWidget(parent),
        m_editor(nullptr)
    {
    }

}
