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
                Property(name, displayName, dataSource, parent),
                m_minSet(false),
                m_min(0.0f),
                m_maxSet(false),
                m_max(0.0f),
                m_convertRadToDeg(false)
            {
            }

            double minimum() const { return m_min; }
            void setMinimum(double min) { m_min = min; m_minSet = true; }
            void resetMinimum() { m_minSet = false; }
            bool isMinimumSet() const { return m_minSet; }

            double maximum() const { return m_max; }
            void setMaximum(double max) { m_max = max; m_maxSet = true; }
            void resetMaximum() { m_maxSet = false; }
            bool isMaximumSet() const { return m_maxSet; }

            bool convertRadiansToDegrees() const { return m_convertRadToDeg; }
            void setConvertRadiansToDegrees(bool convert) { m_convertRadToDeg = convert; }

            virtual QWidget* createWidget(const QList<Property*>& props) override;

        private:
            bool m_minSet;
            double m_min;
            bool m_maxSet;
            double m_max;
            bool m_convertRadToDeg;
        };

    }

}
