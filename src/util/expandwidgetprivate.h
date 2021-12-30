#pragma once

#include <QToolButton>

namespace Slick {

    namespace Util {

        class ExpandWidgetButton : public QToolButton
        {
            Q_OBJECT

        public:
            ExpandWidgetButton(QWidget* parent = nullptr) : QToolButton(parent) {}

            virtual QSize minimumSizeHint() const override { return QSize(32, QToolButton::minimumSizeHint().height()); }
        };

    }

}
