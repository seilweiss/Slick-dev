#pragma once

#include "inspector/properties/doublespinbox.h"

#include <QWidget>

namespace Slick {

    namespace Inspector {

        class VectorSpinBoxGroup : public QWidget
        {
            Q_OBJECT

        public:
            VectorSpinBoxGroup(int dimensions, QWidget* parent = nullptr);

            int dimensions() const { return m_spinBoxes.size(); }
            DoubleSpinBox* spinBox(int index) const { return m_spinBoxes[index]; }

        private:
            QList<DoubleSpinBox*> m_spinBoxes;
        };

    }

}
