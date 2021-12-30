#pragma once

#include "inspector/property.h"

namespace Slick {

    namespace Inspector {

        class NumberInputProperty : public Property
        {
            Q_OBJECT
            Q_PROPERTY(bool convertRadiansToDegrees READ convertRadiansToDegrees WRITE setConvertRadiansToDegrees)

        public:
            NumberInputProperty(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent), m_convertRadToDeg(false) {}

            bool convertRadiansToDegrees() const { return m_convertRadToDeg; }
            void setConvertRadiansToDegrees(bool convert) { m_convertRadToDeg = convert; }

            virtual QWidget* createWidget(const QList<Property*>& props) override;

        private:
            bool m_convertRadToDeg;
        };

    }

}
