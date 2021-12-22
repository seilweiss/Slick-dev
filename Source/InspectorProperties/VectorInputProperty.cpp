#include "InspectorProperties/VectorInputProperty.h"

#include "InspectorProperties/InspectorPropertiesCommon.h"

#include <QHBoxLayout>
#include <QLabel>

#include <glm/glm.hpp>
#include <limits>

namespace Slick {

    namespace {

        template <class T, int N> QWidget* createVectorInput(const QList<InspectorProperty*>& props)
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
                    for (InspectorProperty* prop : props)
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

    QWidget* VectorInputProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        switch (props[0]->dataSource().type())
        {
        case InspectorDataSource::Vector2: return createVectorInput<Vector2, 2>(props);
        case InspectorDataSource::Vector3: return createVectorInput<Vector3, 3>(props);
        case InspectorDataSource::Vector4: return createVectorInput<Vector4, 4>(props);
        case InspectorDataSource::Color: return createVectorInput<Vector4, 4>(props);
        case InspectorDataSource::ColorF: return createVectorInput<Vector4, 4>(props);
        default: Q_ASSERT(false); return nullptr;
        }
    }

}
