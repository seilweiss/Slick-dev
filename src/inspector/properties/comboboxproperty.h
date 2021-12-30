#pragma once

#include "inspector/property.h"

namespace Slick {

    namespace Inspector {

        class ComboBoxProperty : public Property
        {
            Q_OBJECT
            Q_PROPERTY(QStringList items READ items)

        public:
            ComboBoxProperty(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent), m_items(QStringList()) {}

            ComboBoxProperty(const QString& name, const QString& displayName, const DataSource& dataSource, const QStringList& items, QObject* parent = nullptr) :
                Property(name, displayName, dataSource, parent), m_items(items) {}

            QStringList& items() { return m_items; }
            const QStringList& items() const { return m_items; }

            virtual QWidget* createWidget(const QList<Property*>& props) override;

        private:
            QStringList m_items;
        };

    }

}
