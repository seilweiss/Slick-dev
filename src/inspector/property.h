#pragma once

#include "inspector/datasource.h"

#include <QWidget>

Q_MOC_INCLUDE("inspector/group.h")

namespace Slick {

    namespace Inspector {

        class Group;

        class Property : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(Group* parentGroup READ parentGroup WRITE setParentGroup NOTIFY parentGroupChanged)
            Q_PROPERTY(QString id READ id CONSTANT)
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
            Q_PROPERTY(DataSource dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)
            Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibilityChanged)
            Q_PROPERTY(bool nameVisible READ nameVisible WRITE setNameVisible NOTIFY nameVisibilityChanged)
            Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
            Q_PROPERTY(int nameStretch READ nameStretch WRITE setNameStretch NOTIFY nameStretchChanged)
            Q_PROPERTY(int widgetStretch READ widgetStretch WRITE setWidgetStretch NOTIFY widgetStretchChanged)
            Q_PROPERTY(QString helpText READ helpText WRITE setHelpText NOTIFY helpTextChanged)
            Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
            Q_PROPERTY(bool exclusive READ exclusive WRITE setExclusive NOTIFY exclusiveChanged)

        public:
            Property(const QString& name, const QString& displayName, const DataSource& dataSource, QObject* parent = nullptr);
            virtual ~Property();

            Group* parentGroup() const { return m_parentGroup; }
            void setParentGroup(Group* group) { m_parentGroup = group; emit parentGroupChanged(group); }

            QString id() const;

            QString name() const { return m_name; }
            void setName(const QString& name) { m_name = name; emit nameChanged(name); }

            QString displayName() const { return m_displayName; }
            void setDisplayName(const QString& displayName) { m_displayName = displayName; emit displayNameChanged(displayName); }

            DataSource dataSource() const { return m_dataSource; }
            void setDataSource(const DataSource& dataSource) { m_dataSource = dataSource; emit dataSourceChanged(dataSource); }

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

            bool enabled() const { return m_enabled; }
            void setEnabled(bool enabled) { m_enabled = enabled; emit enabledChanged(enabled); }

            bool exclusive() const { return m_exclusive; }
            void setExclusive(bool exclusive) { m_exclusive = exclusive; }

            void notifyDataChanged() { emit dataChanged(); }

            void requestRefresh() { emit refreshRequested(); }

            virtual QWidget* createWidget(const QList<Property*>& props) = 0;
            virtual void updateWidget(QWidget* widget, const QList<Property*>& props) { Q_UNUSED(widget); Q_UNUSED(props); }

        signals:
            void dataChanged();
            void refreshRequested();
            void parentGroupChanged(Slick::Inspector::Group* group);
            void nameChanged(const QString& name);
            void displayNameChanged(const QString& name);
            void dataSourceChanged(const Slick::Inspector::DataSource& dataSource);
            void visibilityChanged(bool visible);
            void nameVisibilityChanged(bool visible);
            void orientationChanged(Qt::Orientation orientation);
            void nameStretchChanged(int nameStretch);
            void widgetStretchChanged(int widgetStretch);
            void helpTextChanged(const QString& helpText);
            void enabledChanged(bool enabled);
            void exclusiveChanged(bool exclusive);

        private:
            Group* m_parentGroup;
            QString m_name;
            QString m_displayName;
            DataSource m_dataSource;
            bool m_visible;
            bool m_nameVisible;
            Qt::Orientation m_orientation;
            int m_nameStretch;
            int m_widgetStretch;
            QString m_helpText;
            bool m_enabled;
            bool m_exclusive;
        };

    }

}
