#include "inspector/properties/numberinputproperty.h"

#include "inspector/properties/intspinbox.h"
#include "inspector/properties/doublespinbox.h"

#include <glm/glm.hpp>
#include <limits>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class T, class W> QWidget* createSpinBox(const QList<Property*>& props)
            {
                W* spinBox = new W;

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

            template <class T, class W> void updateSpinBox(QWidget* widget, const QList<Property*>&props, bool isUInt32 = false)
            {
                W* spinBox = qobject_cast<W*>(widget);
                NumberInputProperty* mainProp = (NumberInputProperty*)props[0];
                T value = mainProp->dataSource().data<T>();
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

                T minimum = mainProp->isMinimumSet() ? (T)mainProp->minimum() : std::numeric_limits<T>::lowest();
                T maximum = mainProp->isMaximumSet() ? (T)mainProp->maximum() : (isUInt32 ? std::numeric_limits<int>::max() : std::numeric_limits<T>::max());

                spinBox->blockSignals(true);
                spinBox->setEmpty(!match);
                spinBox->setRange(minimum, maximum);
                spinBox->setValue(mainProp->convertRadiansToDegrees() ? glm::degrees((float)value) : value);
                spinBox->blockSignals(false);
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
            case DataSource::UInt32: return createSpinBox<uint32_t, IntSpinBox>(props);
            case DataSource::Float: return createSpinBox<float, DoubleSpinBox>(props);
            case DataSource::Double: return createSpinBox<double, DoubleSpinBox>(props);
            default: return createSpinBox<int32_t, IntSpinBox>(props);
            }
        }

        void NumberInputProperty::updateWidget(QWidget* widget, const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Int8: updateSpinBox<int8_t, IntSpinBox>(widget, props); break;
            case DataSource::Int16: updateSpinBox<int16_t, IntSpinBox>(widget, props); break;
            case DataSource::Int32: updateSpinBox<int32_t, IntSpinBox>(widget, props); break;
            case DataSource::UInt8: updateSpinBox<uint8_t, IntSpinBox>(widget, props); break;
            case DataSource::UInt16: updateSpinBox<uint16_t, IntSpinBox>(widget, props); break;
            case DataSource::UInt32: updateSpinBox<uint32_t, IntSpinBox>(widget, props, true); break;
            case DataSource::Float: updateSpinBox<float, DoubleSpinBox>(widget, props); break;
            case DataSource::Double: updateSpinBox<double, DoubleSpinBox>(widget, props); break;
            default: updateSpinBox<int32_t, IntSpinBox>(widget, props); break;
            }
        }

    }

}
