#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class NumberInputProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        NumberInputProperty(const QString& name, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;
    };

}
