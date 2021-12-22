#include "InspectorProperties/NumberInputProperty.h"

#include "InspectorProperties/InspectorPropertiesCommon.h"

#include <glm/glm.hpp>
#include <limits>

namespace Slick {

    namespace {

        template <class T, class W> QWidget* createSpinBox(const QList<InspectorProperty*>& props)
        {
            W* spinBox = new W;
            T value = props[0]->dataSource().data<T>();
            bool match = true;

            for (int i = 1; i < props.size(); i++)
            {
                T data = props[i]->dataSource().data<T>();

                if (data != value)
                {
                    match = false;
                    break;
                }
            }

            spinBox->setEmpty(!match);
            spinBox->setRange(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());
            spinBox->setValue(((NumberInputProperty*)props[0])->convertRadiansToDegrees() ? glm::degrees((float)value) : value);

            QObject::connect(spinBox, &W::valueChanged, [=](T value)
            {
                for (InspectorProperty* prop : props)
                {
                    prop->dataSource().setData(((NumberInputProperty*)prop)->convertRadiansToDegrees() ? glm::radians((float)value) : value);
                    prop->notifyDataChanged();
                }
            });

            return spinBox;
        }

    }

    QWidget* NumberInputProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        switch (props[0]->dataSource().type())
        {
        case InspectorDataSource::Int8: return createSpinBox<int8_t, IntSpinBox>(props);
        case InspectorDataSource::Int16: return createSpinBox<int16_t, IntSpinBox>(props);
        case InspectorDataSource::Int32: return createSpinBox<int32_t, IntSpinBox>(props);
        case InspectorDataSource::UInt8: return createSpinBox<uint8_t, IntSpinBox>(props);
        case InspectorDataSource::UInt16: return createSpinBox<uint16_t, IntSpinBox>(props);
        case InspectorDataSource::UInt32: return createSpinBox<uint32_t, IntSpinBox>(props);
        case InspectorDataSource::Float: return createSpinBox<float, DoubleSpinBox>(props);
        case InspectorDataSource::Double: return createSpinBox<double, DoubleSpinBox>(props);
        default: return createSpinBox<int32_t, IntSpinBox>(props);
        }
    }

}
