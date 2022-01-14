#pragma once

#include "inspector/property.h"

namespace Slick {

    namespace Inspector {

        class VectorInputProperty : public Property
        {
            Q_OBJECT
            Q_PROPERTY(bool convertRadiansToDegrees READ convertRadiansToDegrees WRITE setConvertRadiansToDegrees)

        public:
            VectorInputProperty(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent),
                m_convertRadToDeg(false)
            {
                //setNameStretch(0);
                //setWidgetStretch(1);

                setOrientation(Qt::Vertical);
            }

            bool convertRadiansToDegrees() const { return m_convertRadToDeg; }
            void setConvertRadiansToDegrees(bool convert) { m_convertRadToDeg = convert; }

            virtual QWidget* createWidget(const QList<Property*>& props) override;
            virtual void updateWidget(QWidget* widget, const QList<Property*>& props) override;

        private:
            bool m_convertRadToDeg;
        };

    }

}
