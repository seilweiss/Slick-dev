#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class UInt16InspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        UInt16InspectorProperty(const QString& name, uint16_t* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        uint16_t data() const { return *(uint16_t*)InspectorProperty::dataSource(); }
        void setData(uint16_t data) { *(uint16_t*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
