#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class Int32InspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        Int32InspectorProperty(const QString& name, int32_t* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        int32_t data() const { return *(int32_t*)InspectorProperty::dataSource(); }
        void setData(int32_t data) { *(int32_t*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
