#include "inspector/properties/vectorinputproperty.h"

#include "inspector/properties/vectorspinboxgroup.h"

#include <QHBoxLayout>
#include <QLabel>

#include <glm/glm.hpp>
#include <limits>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class T> QWidget* createVectorInput(int dimensions, const QList<Property*>& props)
            {
                VectorSpinBoxGroup* group = new VectorSpinBoxGroup(dimensions);

                for (int i = 0; i < dimensions; i++)
                {
                    DoubleSpinBox* spinBox = group->spinBox(i);

                    QObject::connect(spinBox, &DoubleSpinBox::valueChanged, [=](double value)
                    {
                        for (Property* prop : props)
                        {
                            T data = prop->dataSource().data<T>();
                            ((float*)&data)[i] = ((VectorInputProperty*)prop)->convertRadiansToDegrees() ? glm::radians((float)value) : value;

                            prop->dataSource().setData(data);
                            prop->notifyDataChanged();
                        }
                    });
                }

                return group;
            }

            template <class T> void updateVectorInput(QWidget* widget, const QList<Property*>& props)
            {
                VectorSpinBoxGroup* group = (VectorSpinBoxGroup*)widget;
                T value = props[0]->dataSource().data<T>();

                for (int i = 0; i < group->dimensions(); i++)
                {
                    DoubleSpinBox* spinBox = group->spinBox(i);
                    bool match = true;

                    for (int j = 1; j < props.size(); j++)
                    {
                        T data = props[j]->dataSource().data<T>();

                        if (((float*)&data)[j] != ((float*)&value)[j])
                        {
                            match = false;
                            break;
                        }
                    }

                    spinBox->setEmpty(!match);
                    spinBox->setValue(((VectorInputProperty*)props[0])->convertRadiansToDegrees() ? glm::degrees(((float*)&value)[i]) : ((float*)&value)[i]);
                }
            }

        }

        QWidget* VectorInputProperty::createWidget(const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Vector2: return createVectorInput<Core::Vector2>(2, props);
            case DataSource::Vector3: return createVectorInput<Core::Vector3>(3, props);
            case DataSource::Vector4: return createVectorInput<Core::Vector4>(4, props);
            case DataSource::Color: return createVectorInput<Core::Vector4>(4, props);
            case DataSource::ColorF: return createVectorInput<Core::Vector4>(4, props);
            default: Q_ASSERT(false); return nullptr;
            }
        }

        void VectorInputProperty::updateWidget(QWidget* widget, const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Vector2: updateVectorInput<Core::Vector2>(widget, props); break;
            case DataSource::Vector3: updateVectorInput<Core::Vector3>(widget, props); break;
            case DataSource::Vector4: updateVectorInput<Core::Vector4>(widget, props); break;
            case DataSource::Color: updateVectorInput<Core::Vector4>(widget, props); break;
            case DataSource::ColorF: updateVectorInput<Core::Vector4>(widget, props); break;
            default: Q_ASSERT(false); break;
            }
        }

    }

}
