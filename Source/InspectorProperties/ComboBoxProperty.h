#pragma once

#include "Core/InspectorProperty.h"

namespace Slick {

    class ComboBoxProperty : public InspectorProperty
    {
        Q_OBJECT
        Q_PROPERTY(QStringList items READ items)

    public:
        ComboBoxProperty(const QString& name, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent), m_items(QStringList()) {}

        ComboBoxProperty(const QString& name, const InspectorDataSource& dataSource, const QStringList& items, QObject* parent = nullptr) :
            InspectorProperty(name, dataSource, parent), m_items(items) {}

        QStringList& items() { return m_items; }
        const QStringList& items() const { return m_items; }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) override;

    private:
        QStringList m_items;
    };

}
