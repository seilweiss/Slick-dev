#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class NumberInputProperty : public InspectorProperty
    {
        Q_OBJECT
        Q_PROPERTY(bool convertRadiansToDegrees READ convertRadiansToDegrees WRITE setConvertRadiansToDegrees)

    public:
        NumberInputProperty(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, displayName, dataSource, parent), m_convertRadToDeg(false) {}

        bool convertRadiansToDegrees() const { return m_convertRadToDeg; }
        void setConvertRadiansToDegrees(bool convert) { m_convertRadToDeg = convert; }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;

    private:
        bool m_convertRadToDeg;
    };

}
