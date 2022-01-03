#pragma once

#include "inspector/property.h"

namespace Slick {

    namespace Inspector {

        class CheckBoxProperty : public Property
        {
            Q_OBJECT
            Q_PROPERTY(uint32_t mask READ mask WRITE setMask)

        public:
            CheckBoxProperty(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent), m_mask(0xFFFFFFFF) {}

            CheckBoxProperty(const QString& name, const QString& displayName, const DataSource& dataSource, uint32_t mask, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent), m_mask(mask) {}

            uint32_t mask() const { return m_mask; }
            void setMask(uint32_t mask) { m_mask = mask; }

            virtual QWidget* createWidget(const QList<Property*>& props) override;
            virtual void updateWidget(QWidget* widget, const QList<Property*>& props) override;

        private:
            uint32_t m_mask;
        };

    }

}
