#pragma once

#include "inspector/property.h"
#include "inspector/group.h"

#include "util/expandwidget.h"

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Slick {

    namespace Panels {

        namespace InspectorPanelPrivate {

            class PropertyWidget : public QWidget
            {
                Q_OBJECT
                Q_PROPERTY(QList<Inspector::Property*> properties READ properties)

            public:
                PropertyWidget(const QList<Inspector::Property*>& props, QWidget* parent = nullptr);

                const QList<Inspector::Property*>& properties() const { return m_props; }

            signals:
                void visibilityChanged(bool visible);

            protected:
                virtual void showEvent(QShowEvent* event) override;
                virtual void hideEvent(QHideEvent* event) override;

            private:
                QList<Inspector::Property*> m_props;
                QBoxLayout* m_layout;
                QLabel* m_label;
                QWidget* m_widget;
                bool m_firstRefresh;

                void refresh();
            };

            class GroupWidget : public QWidget
            {
                Q_OBJECT
                Q_PROPERTY(QList<Inspector::Group*> groups READ groups)

            public:
                GroupWidget(const QList<Inspector::Group*>& groups, QWidget* parent = nullptr);

                const QList<Inspector::Group*>& groups() const { return m_groups; }

            signals:
                void refreshStarted();
                void refreshFinished();

            private:
                QList<Inspector::Group*> m_groups;
                QVBoxLayout* m_layout;
                Util::ExpandWidget* m_expandWidget;
                QWidget* m_content;
                QVBoxLayout* m_contentLayout;
                bool m_firstRefresh;

                void refreshGroup();
                void refreshWidget();
            };

            QString makeDisplayName(const QString& name);

        }

    }

}
