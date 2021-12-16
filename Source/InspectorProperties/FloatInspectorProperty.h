#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class FloatInspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        FloatInspectorProperty(const QString& name, float* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        float data() const { return *(float*)InspectorProperty::dataSource(); }
        void setData(float data) { *(float*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
