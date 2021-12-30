#include "inspector/properties/vectorinputproperty.h"

#include "inspector/properties/doublespinbox.h"

#include <QHBoxLayout>
#include <QLabel>

#include <glm/glm.hpp>
#include <limits>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class T, int N> QWidget* createVectorInput(const QList<Property*>& props)
            {
                static const QStringList labels = { "X", "Y", "Z", "W" };

                QWidget* container = new QWidget;
                QHBoxLayout* layout = new QHBoxLayout;

                layout->setContentsMargins(0, 0, 0, 0);
                container->setLayout(layout);

                T value = props[0]->dataSource().data<T>();

                for (int n = 0; n < N; n++)
                {
                    DoubleSpinBox* spinBox = new DoubleSpinBox;

                    layout->addWidget(new QLabel(labels[n]));
                    layout->addWidget(spinBox, 1);

                    bool match = true;

                    for (int i = 1; i < props.size(); i++)
                    {
                        T data = props[i]->dataSource().data<T>();

                        if (((float*)&data)[n] != ((float*)&value)[n])
                        {
                            match = false;
                            break;
                        }
                    }

                    spinBox->setEmpty(!match);
                    spinBox->setRange(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
                    spinBox->setAlignment(Qt::AlignRight);
                    spinBox->setValue(((VectorInputProperty*)props[0])->convertRadiansToDegrees() ? glm::degrees(((float*)&value)[n]) : ((float*)&value)[n]);

                    QObject::connect(spinBox, &DoubleSpinBox::valueChanged, [=](double value)
                    {
                        for (Property* prop : props)
                        {
                            T data = prop->dataSource().data<T>();
                            ((float*)&data)[n] = ((VectorInputProperty*)prop)->convertRadiansToDegrees() ? glm::radians((float)value) : value;

                            prop->dataSource().setData(data);
                            prop->notifyDataChanged();
                        }
                    });
                }

                return container;
            }

        }

        QWidget* VectorInputProperty::createWidget(const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Vector2: return createVectorInput<Core::Vector2, 2>(props);
            case DataSource::Vector3: return createVectorInput<Core::Vector3, 3>(props);
            case DataSource::Vector4: return createVectorInput<Core::Vector4, 4>(props);
            case DataSource::Color: return createVectorInput<Core::Vector4, 4>(props);
            case DataSource::ColorF: return createVectorInput<Core::Vector4, 4>(props);
            default: Q_ASSERT(false); return nullptr;
            }
        }

    }

}
