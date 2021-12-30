#include "inspector/properties/comboboxproperty.h"

#include "inspector/properties/combobox.h"

namespace Slick {

    namespace Inspector {

        namespace {

            QWidget* createComboBox(const QList<Property*>& props)
            {
                ComboBox* comboBox = new ComboBox;
                int index = props[0]->dataSource().data<int>();
                bool match = true;

                for (int i = 1; i < props.size(); i++)
                {
                    int data = props[i]->dataSource().data<int>();

                    if (data != index)
                    {
                        match = false;
                        break;
                    }
                }

                comboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
                comboBox->addItems(((ComboBoxProperty*)props[0])->items());
                comboBox->setCurrentIndex(match ? index : -1);

                QObject::connect(comboBox, &QComboBox::currentIndexChanged, [=](int index)
                {
                    for (Property* prop : props)
                    {
                        prop->dataSource().setData<int>(index);
                        prop->notifyDataChanged();
                    }
                });

                return comboBox;
            }

        }

        QWidget* ComboBoxProperty::createWidget(const QList<Property*>& props)
        {
            return createComboBox(props);
        }

    }

}
