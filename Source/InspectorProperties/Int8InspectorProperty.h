#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class Int8InspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        Int8InspectorProperty(const QString& name, int8_t* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        int8_t data() const { return *(int8_t*)InspectorProperty::dataSource(); }
        void setData(int8_t data) { *(int8_t*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
