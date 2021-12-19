#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class VectorInputProperty : public InspectorProperty
    {
        Q_OBJECT

    public:
        VectorInputProperty(const QString& name, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent)
        {
            setNameStretch(0);
            setWidgetStretch(1);
        }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;
    };

}
