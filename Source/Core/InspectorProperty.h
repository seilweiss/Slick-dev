#pragma once

#include <QWidget>

namespace Slick {

    class InspectorProperty : public QObject
    {
        Q_OBJECT

    public:
        InspectorProperty(const QString& name, void* dataSource, QObject* parent = nullptr) :
            QObject(parent),
            m_name(name),
            m_displayName(),
            m_dataSource(dataSource),
            m_nameVisible(true),
            m_orientation(Qt::Horizontal)
        {
            Q_ASSERT(m_dataSource);
        }

        QString name() const { return m_name; }
        void setName(const QString& name) { m_name = name; }

        QString displayName() const { return m_displayName; }
        void setDisplayName(const QString& name) { m_name = name; }

        void* dataSource() const { return m_dataSource; }
        void setDataSource(void* dataSource) { m_dataSource = dataSource; }

        bool nameVisible() const { return m_nameVisible; }
        void setNameVisible(bool visible) { m_nameVisible = visible; }

        Qt::Orientation orientation() const { return m_orientation; }
        void setOrientation(Qt::Orientation orientation) { m_orientation = orientation; }

        void notifyDataChanged() { emit dataChanged(); }

        virtual QWidget* createWidget(const QVector<InspectorProperty*>& props) = 0;

    signals:
        void dataChanged();

    private:
        QString m_name;
        QString m_displayName;
        void* m_dataSource;
        bool m_nameVisible;
        Qt::Orientation m_orientation;
    };

}
