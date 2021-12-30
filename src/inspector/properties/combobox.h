#pragma once

#include "inspector/properties/wheelignorer.h"

#include <QComboBox>

namespace Slick {

    namespace Inspector {

        class ComboBox : public QComboBox
        {
            Q_OBJECT

        public:
            ComboBox(QWidget* parent = nullptr) : QComboBox(parent)
            {
                setFocusPolicy(Qt::StrongFocus);
                installEventFilter(new WheelIgnorer(this));
            }
        };

    }

}
