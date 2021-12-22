#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class VectorInputProperty : public InspectorProperty
    {
        Q_OBJECT
        Q_PROPERTY(bool convertRadiansToDegrees READ convertRadiansToDegrees WRITE setConvertRadiansToDegrees)

    public:
        VectorInputProperty(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, displayName, dataSource, parent),
            m_convertRadToDeg(false)
        {
            //setNameStretch(0);
            //setWidgetStretch(1);

            setOrientation(Qt::Vertical);
        }

        bool convertRadiansToDegrees() const { return m_convertRadToDeg; }
        void setConvertRadiansToDegrees(bool convert) { m_convertRadToDeg = convert; }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;

    private:
        bool m_convertRadToDeg;
    };

}
