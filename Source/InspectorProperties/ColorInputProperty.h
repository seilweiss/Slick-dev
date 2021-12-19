#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class ColorInputProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        ColorInputProperty(const QString& name, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent) {}

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;
    };

}
