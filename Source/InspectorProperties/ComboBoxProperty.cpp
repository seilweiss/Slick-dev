#include "InspectorProperties/ComboBoxProperty.h"

#include <QComboBox>

namespace Slick {

    namespace {

        QWidget* createComboBox(const QList<InspectorProperty*>& props)
        {
            QComboBox* comboBox = new QComboBox;
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
                for (InspectorProperty* prop : props)
                {
                    prop->dataSource().setData<int>(index);
                    prop->notifyDataChanged();
                }
            });

            return comboBox;
        }

    }

    QWidget* ComboBoxProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        return createComboBox(props);
    }

}
