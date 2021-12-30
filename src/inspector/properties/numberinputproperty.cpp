#include "inspector/properties/numberinputproperty.h"

#include "inspector/properties/intspinbox.h"
#include "inspector/properties/doublespinbox.h"

#include <glm/glm.hpp>
#include <limits>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class T, class W> QWidget* createSpinBox(const QList<Property*>& props, bool isUInt32 = false)
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
                spinBox->setRange(std::numeric_limits<T>::lowest(), isUInt32 ? std::numeric_limits<int>::max() : std::numeric_limits<T>::max());
                spinBox->setValue(((NumberInputProperty*)props[0])->convertRadiansToDegrees() ? glm::degrees((float)value) : value);

                QObject::connect(spinBox, &W::valueChanged, [=](T value)
                {
                    for (Property* prop : props)
                    {
                        prop->dataSource().setData(((NumberInputProperty*)prop)->convertRadiansToDegrees() ? glm::radians((float)value) : value);
                        prop->notifyDataChanged();
                    }
                });

                return spinBox;
            }

        }

        QWidget* NumberInputProperty::createWidget(const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Int8: return createSpinBox<int8_t, IntSpinBox>(props);
            case DataSource::Int16: return createSpinBox<int16_t, IntSpinBox>(props);
            case DataSource::Int32: return createSpinBox<int32_t, IntSpinBox>(props);
            case DataSource::UInt8: return createSpinBox<uint8_t, IntSpinBox>(props);
            case DataSource::UInt16: return createSpinBox<uint16_t, IntSpinBox>(props);
            case DataSource::UInt32: return createSpinBox<uint32_t, IntSpinBox>(props, true);
            case DataSource::Float: return createSpinBox<float, DoubleSpinBox>(props);
            case DataSource::Double: return createSpinBox<double, DoubleSpinBox>(props);
            default: return createSpinBox<int32_t, IntSpinBox>(props);
            }
        }

    }

}
