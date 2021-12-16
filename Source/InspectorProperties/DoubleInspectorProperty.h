#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class DoubleInspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        DoubleInspectorProperty(const QString& name, double* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        double data() const { return *(double*)InspectorProperty::dataSource(); }
        void setData(double data) { *(double*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
