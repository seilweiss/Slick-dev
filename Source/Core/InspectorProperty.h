#pragma once

#include "Core/InspectorDataSource.h"

#include <QWidget>

namespace Slick {

    class InspectorProperty : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName)
        Q_PROPERTY(InspectorDataSource dataSource READ dataSource WRITE setDataSource)
        Q_PROPERTY(bool nameVisible READ nameVisible WRITE setNameVisible)
        Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
        Q_PROPERTY(int nameStretch READ nameStretch WRITE setNameStretch)
        Q_PROPERTY(int widgetStretch READ widgetStretch WRITE setWidgetStretch)

    public:
        InspectorProperty(const QString& name, const InspectorDataSource& dataSource, QObject* parent = nullptr) :
            QObject(parent),
            m_name(name),
            m_displayName(),
            m_dataSource(dataSource),
            m_nameVisible(true),
            m_orientation(Qt::Horizontal),
            m_nameStretch(1),
            m_widgetStretch(1)
        {
        }

        QString name() const { return m_name; }
        void setName(const QString& name) { m_name = name; }

        QString displayName() const { return m_displayName; }
        void setDisplayName(const QString& name) { m_name = name; }

        InspectorDataSource dataSource() const { return m_dataSource; }
        void setDataSource(const InspectorDataSource& dataSource) { m_dataSource = dataSource; }

        bool nameVisible() const { return m_nameVisible; }
        void setNameVisible(bool visible) { m_nameVisible = visible; }

        Qt::Orientation orientation() const { return m_orientation; }
        void setOrientation(Qt::Orientation orientation) { m_orientation = orientation; }

        int nameStretch() const { return m_nameStretch; }
        void setNameStretch(int nameStretch) { m_nameStretch = nameStretch; }

        int widgetStretch() const { return m_widgetStretch; }
        void setWidgetStretch(int widgetStretch) { m_widgetStretch = widgetStretch; }

        void notifyDataChanged() { emit dataChanged(); }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) = 0;

    signals:
        void dataChanged();

    private:
        QString m_name;
        QString m_displayName;
        InspectorDataSource m_dataSource;
        bool m_nameVisible;
        Qt::Orientation m_orientation;
        int m_nameStretch;
        int m_widgetStretch;
    };

}
