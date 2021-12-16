#pragma once

#include <QWidget>

class QVBoxLayout;
class QToolButton;
class QFrame;

namespace Slick {

    class ExpanderWidget : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(QWidget* widget READ widget WRITE setWidget)
        Q_PROPERTY(QString title READ title WRITE setTitle)
        Q_PROPERTY(bool isExpanded READ isExpanded)

    public:
        ExpanderWidget(const QString& title, QWidget* parent = nullptr);
        ExpanderWidget(QWidget* parent = nullptr);

        QWidget* widget() const { return m_widget; }
        void setWidget(QWidget* widget);

        QString title() const;
        void setTitle(const QString& title);

        bool isExpanded() const;
        void setExpanded(bool expanded);

        void expand() { setExpanded(true); }
        void collapse() { setExpanded(false); }

    private:
        QVBoxLayout* m_layout;
        QToolButton* m_headerButton;
        QWidget* m_widget;
        QFrame* m_widgetFrame;
        QVBoxLayout* m_widgetFrameLayout;
    };

}
