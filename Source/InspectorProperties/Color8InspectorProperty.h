#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class Color8InspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        Color8InspectorProperty(const QString& name, uint8_t(*dataSource)[4], QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        uint8_t* data() const { return *(uint8_t(*)[4])InspectorProperty::dataSource(); }
        void setData(uint8_t* data) { memcpy(*(uint8_t(*)[4])InspectorProperty::dataSource(), data, 4); }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
