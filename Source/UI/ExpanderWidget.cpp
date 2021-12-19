#include "UI/ExpanderWidget.h"

#include "UI/ExpanderWidgetPrivate.h"

#include <QVBoxLayout>
#include <QFrame>

namespace Slick {

    ExpanderWidget::ExpanderWidget(const QString& title, QWidget* parent)
        : QWidget(parent),
          m_layout(new QVBoxLayout),
          m_headerButton(new ExpanderWidgetButton),
          m_widget(nullptr),
          m_widgetFrame(new QFrame),
          m_widgetFrameLayout(new QVBoxLayout)
    {
        m_headerButton->setStyleSheet("QToolButton { margin: 0; }");
        m_headerButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_headerButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        m_headerButton->setArrowType(Qt::DownArrow);
        m_headerButton->setIconSize(QSize(8, 8));
        m_headerButton->setText(title);
        m_headerButton->setCheckable(true);
        m_headerButton->setChecked(true);

        m_widgetFrame->setStyleSheet("QFrame { margin: 0; }");
        m_widgetFrame->setFrameShape(QFrame::StyledPanel);
        m_widgetFrame->setLayout(m_widgetFrameLayout);

        m_widgetFrameLayout->setContentsMargins(0, 0, 0, 0);

        m_layout->setContentsMargins(0, 0, 0, 0);
        m_layout->setSpacing(0);
        m_layout->addWidget(m_headerButton, 0, Qt::AlignTop);
        m_layout->addWidget(m_widgetFrame);
        setLayout(m_layout);

        m_widgetFrame->setVisible(true);

        connect(m_headerButton, &QToolButton::toggled, this, [=](bool checked)
        {
            m_headerButton->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
            m_widgetFrame->setVisible(isExpanded());

            emit toggled(checked);
        });
    }

    ExpanderWidget::ExpanderWidget(QWidget* parent)
        : ExpanderWidget(QString(), parent)
    {
    }

    void ExpanderWidget::setWidget(QWidget* widget)
    {
        if (m_widget)
        {
            m_widgetFrameLayout->removeWidget(m_widget);
        }

        m_widget = widget;

        m_widgetFrameLayout->addWidget(widget);
    }

    QString ExpanderWidget::title() const
    {
        return m_headerButton->text();
    }

    void ExpanderWidget::setTitle(const QString& title)
    {
        m_headerButton->setText(title);
    }

    bool ExpanderWidget::isExpanded() const
    {
        return m_headerButton->isChecked();
    }

    void ExpanderWidget::setExpanded(bool expanded)
    {
        m_headerButton->setChecked(expanded);
    }

}
