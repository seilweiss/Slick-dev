#pragma once

#include <QToolButton>

namespace Slick {

    class ExpanderWidgetButton : public QToolButton
    {
        Q_OBJECT

    public:
        ExpanderWidgetButton(QWidget* parent = nullptr) : QToolButton(parent) {}

        virtual QSize minimumSizeHint() const override { return QSize(32, QToolButton::minimumSizeHint().height()); }
    };

}
