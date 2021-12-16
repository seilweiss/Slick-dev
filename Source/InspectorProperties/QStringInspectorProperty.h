#pragma once

#include "InspectorProperties/AbstractStringInspectorProperty.h"

namespace Slick {

    class QStringInspectorProperty : public AbstractStringInspectorProperty
    {
        Q_OBJECT

    public:
        QStringInspectorProperty(const QString& name, QString* dataSource, QObject* parent = nullptr) :
            AbstractStringInspectorProperty(name, dataSource, parent) {}

        QString data() const { return *(QString*)InspectorProperty::dataSource(); }
        void setData(const QString& data) { *(QString*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
