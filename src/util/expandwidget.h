#pragma once

#include <QWidget>

class QVBoxLayout;
class QFrame;

namespace Slick {

    namespace Util {

        class ExpandWidgetButton;

        class ExpandWidget : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(QWidget* widget READ widget WRITE setWidget)
            Q_PROPERTY(QString title READ title WRITE setTitle)
            Q_PROPERTY(QString toolTip READ toolTip WRITE setToolTip)
            Q_PROPERTY(bool isExpanded READ isExpanded)

        public:
            ExpandWidget(const QString& title, QWidget* parent = nullptr);
            ExpandWidget(QWidget* parent = nullptr);

            QWidget* widget() const { return m_widget; }
            void setWidget(QWidget* widget);

            QString title() const;
            void setTitle(const QString& title);

            QString toolTip() const;
            void setToolTip(const QString& tooltip);

            bool isExpanded() const;
            void setExpanded(bool expanded);

            void expand() { setExpanded(true); }
            void collapse() { setExpanded(false); }

        signals:
            void toggled(bool expanded);

        private:
            QString m_toolTipOverride;
            QVBoxLayout* m_layout;
            ExpandWidgetButton* m_headerButton;
            QWidget* m_widget;
            QFrame* m_widgetFrame;
            QVBoxLayout* m_widgetFrameLayout;

            void updateToolTip();
        };

    }

}
