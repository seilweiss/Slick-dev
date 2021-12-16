#pragma once

#include "InspectorProperties/AbstractStringInspectorProperty.h"

namespace Slick {

    class StdStringInspectorProperty : public AbstractStringInspectorProperty
    {
        Q_OBJECT

    public:
        StdStringInspectorProperty(const QString& name, std::string* dataSource, QObject* parent = nullptr) :
            AbstractStringInspectorProperty(name, dataSource, parent) {}

        std::string data() const { return *(std::string*)InspectorProperty::dataSource(); }
        void setData(const std::string& data) { *(std::string*)InspectorProperty::dataSource() = data; }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) override;
    };

}
