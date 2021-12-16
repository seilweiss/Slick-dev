#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class UInt32InspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        UInt32InspectorProperty(const QString& name, uint32_t* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        uint32_t data() const { return *(uint32_t*)InspectorProperty::dataSource(); }
        void setData(int32_t data) { *(uint32_t*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
