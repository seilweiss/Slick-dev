#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class UInt8InspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        UInt8InspectorProperty(const QString& name, uint8_t* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        uint8_t data() const { return *(uint8_t*)InspectorProperty::dataSource(); }
        void setData(uint8_t data) { *(uint8_t*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
