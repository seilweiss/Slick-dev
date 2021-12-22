#pragma once

#include "Core/InspectorDataSource.h"

#include <QWidget>

Q_MOC_INCLUDE("Core/InspectorGroup.h")

namespace Slick {

    class InspectorGroup;

    class InspectorProperty : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(InspectorGroup* parentGroup READ parentGroup WRITE setParentGroup NOTIFY parentGroupChanged)
        Q_PROPERTY(QString id READ id CONSTANT)
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
        Q_PROPERTY(InspectorDataSource dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)
        Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibilityChanged)
        Q_PROPERTY(bool nameVisible READ nameVisible WRITE setNameVisible NOTIFY nameVisibilityChanged)
        Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
        Q_PROPERTY(int nameStretch READ nameStretch WRITE setNameStretch NOTIFY nameStretchChanged)
        Q_PROPERTY(int widgetStretch READ widgetStretch WRITE setWidgetStretch NOTIFY widgetStretchChanged)
        Q_PROPERTY(QString helpText READ helpText WRITE setHelpText NOTIFY helpTextChanged)

    public:
        InspectorProperty(const QString& name, const QString& displayName, const InspectorDataSource& dataSource, QObject* parent = nullptr);
        virtual ~InspectorProperty();

        InspectorGroup* parentGroup() const { return m_parentGroup; }
        void setParentGroup(InspectorGroup* group) { m_parentGroup = group; emit parentGroupChanged(group); }

        QString id() const;

        QString name() const { return m_name; }
        void setName(const QString& name) { m_name = name; emit nameChanged(name); }

        QString displayName() const { return m_displayName; }
        void setDisplayName(const QString& displayName) { m_displayName = displayName; emit displayNameChanged(displayName); }

        InspectorDataSource dataSource() const { return m_dataSource; }
        void setDataSource(const InspectorDataSource& dataSource) { m_dataSource = dataSource; emit dataSourceChanged(dataSource); }

        bool visible() const { return m_visible; }
        void setVisible(bool visible) { m_visible = visible; emit visibilityChanged(visible); }

        bool nameVisible() const { return m_nameVisible; }
        void setNameVisible(bool visible) { m_nameVisible = visible; emit nameVisibilityChanged(visible); }

        Qt::Orientation orientation() const { return m_orientation; }
        void setOrientation(Qt::Orientation orientation) { m_orientation = orientation; emit orientationChanged(orientation); }

        int nameStretch() const { return m_nameStretch; }
        void setNameStretch(int nameStretch) { m_nameStretch = nameStretch; emit nameStretchChanged(nameStretch); }

        int widgetStretch() const { return m_widgetStretch; }
        void setWidgetStretch(int widgetStretch) { m_widgetStretch = widgetStretch; emit widgetStretchChanged(widgetStretch); }

        QString helpText() const { return m_helpText; }
        void setHelpText(const QString& helpText) { m_helpText = helpText; emit helpTextChanged(helpText); }

        void notifyDataChanged() { emit dataChanged(); }

        virtual QWidget* createWidget(const QList<InspectorProperty*>& props) = 0;

    signals:
        void dataChanged();
        void parentGroupChanged(Slick::InspectorGroup* group);
        void nameChanged(const QString& name);
        void displayNameChanged(const QString& name);
        void dataSourceChanged(const Slick::InspectorDataSource& dataSource);
        void visibilityChanged(bool visible);
        void nameVisibilityChanged(bool visible);
        void orientationChanged(Qt::Orientation orientation);
        void nameStretchChanged(int nameStretch);
        void widgetStretchChanged(int widgetStretch);
        void helpTextChanged(const QString& helpText);

    private:
        InspectorGroup* m_parentGroup;
        QString m_name;
        QString m_displayName;
        InspectorDataSource m_dataSource;
        bool m_visible;
        bool m_nameVisible;
        Qt::Orientation m_orientation;
        int m_nameStretch;
        int m_widgetStretch;
        QString m_helpText;
    };

}
