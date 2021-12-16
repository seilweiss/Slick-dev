#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class Int16InspectorProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        Int16InspectorProperty(const QString& name, int16_t* dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        int16_t data() const { return *(int16_t*)InspectorProperty::dataSource(); }
        void setData(int16_t data) { *(int16_t*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
