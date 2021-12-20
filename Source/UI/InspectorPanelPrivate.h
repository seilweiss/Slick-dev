#pragma once

#include "Core/InspectorProperty.h"
#include "Core/InspectorGroup.h"

#include "UI/ExpanderWidget.h"

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

namespace Slick {

    namespace InspectorPanelPrivate {

        class InspectorPropertyWidget : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(QList<InspectorProperty*> properties READ properties)

        public:
            InspectorPropertyWidget(const QList<InspectorProperty*>& props, QWidget* parent = nullptr);

            const QList<InspectorProperty*>& properties() const { return m_props; }

        signals:
            void visibilityChanged(bool visible);

        protected:
            virtual void showEvent(QShowEvent* event) override;
            virtual void hideEvent(QHideEvent* event) override;

        private:
            QList<InspectorProperty*> m_props;
            QBoxLayout* m_layout;
            QLabel* m_label;
            QWidget* m_widget;
            bool m_firstRefresh;

            void refresh();
        };

        class InspectorGroupWidget : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(QList<InspectorGroup*> groups READ groups)

        public:
            InspectorGroupWidget(const QList<InspectorGroup*>& groups, QWidget* parent = nullptr);

            const QList<InspectorGroup*>& groups() const { return m_groups; }

        private:
            QList<InspectorGroup*> m_groups;
            QVBoxLayout* m_layout;
            ExpanderWidget* m_expander;
            QWidget* m_content;
            QVBoxLayout* m_contentLayout;
            bool m_firstRefresh;

            void refresh();
        };

        QString makeDisplayName(const QString& name);

    }

}
