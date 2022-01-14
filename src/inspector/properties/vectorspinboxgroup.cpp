#include "inspector/properties/vectorspinboxgroup.h"

#include "inspector/properties/doublespinbox.h"

#include <QHBoxLayout>
#include <QLabel>

namespace Slick {

    namespace Inspector {

        VectorSpinBoxGroup::VectorSpinBoxGroup(int dimensions, QWidget* parent) :
            QWidget(parent)
        {
            static const QStringList labels = { "X", "Y", "Z", "W" };

            QHBoxLayout* mainLayout = new QHBoxLayout;

            mainLayout->setContentsMargins(0, 0, 0, 0);

            for (int i = 0; i < dimensions; i++)
            {
                DoubleSpinBox* spinBox = new DoubleSpinBox;

                spinBox->setRange(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
                spinBox->setAlignment(Qt::AlignRight);

                mainLayout->addWidget(new QLabel(labels[i]));
                mainLayout->addWidget(spinBox, 1);

                m_spinBoxes.append(spinBox);
            }

            setLayout(mainLayout);
        }

    }

}
