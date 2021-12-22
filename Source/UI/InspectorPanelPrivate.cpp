#include "UI/InspectorPanelPrivate.h"

#include <QToolButton>
#include <QPushButton>

namespace Slick {

    namespace InspectorPanelPrivate {

        InspectorPropertyWidget::InspectorPropertyWidget(const QList<InspectorProperty*>& props, QWidget* parent) :
            QWidget(parent),
            m_props(props),
            m_layout(new QBoxLayout(QBoxLayout::LeftToRight)),
            m_label(new QLabel),
            m_widget(props[0]->createWidget(props)),
            m_firstRefresh(true)
        {
            InspectorProperty* mainProp = m_props[0];

            qDebug().noquote() << QString("Creating inspector property widget (id: %1)").arg(mainProp->id());

            m_layout->setContentsMargins(0, 0, 0, 0);
            m_layout->addWidget(m_label);
            m_layout->addWidget(m_widget);

            setLayout(m_layout);

            refresh();

            for (InspectorProperty* prop : m_props)
            {
                connect(prop, &InspectorProperty::nameChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::displayNameChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::dataSourceChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::visibilityChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::nameVisibilityChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::orientationChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::nameStretchChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::widgetStretchChanged, this, &InspectorPropertyWidget::refresh);
                connect(prop, &InspectorProperty::helpTextChanged, this, &InspectorPropertyWidget::refresh);
            }
        }

        void InspectorPropertyWidget::refresh()
        {
            InspectorProperty* mainProp = m_props[0];

            if (!m_firstRefresh)
            {
                qDebug().noquote() << QString("Refreshing inspector property widget (id: %1)").arg(mainProp->id());
            }
            else
            {
                m_firstRefresh = false;
            }

            for (InspectorProperty* prop : m_props)
            {
                if (!prop->visible())
                {
                    setVisible(false);
                    return;
                }
            }

            if (parentWidget())
            {
                setVisible(true);
            }

            if (mainProp->nameVisible())
            {
                m_label->setVisible(true);

                QString displayName = mainProp->displayName();

                if (displayName.isEmpty())
                {
                    if (mainProp->parentGroup() && mainProp->parentGroup()->isList())
                    {
                        displayName = mainProp->name();
                    }
                    else
                    {
                        qDebug().noquote() << QString("Warning: no display name set for property (id: %1)").arg(mainProp->id());
                        displayName = makeDisplayName(mainProp->name());
                    }
                }

                m_label->setText(displayName);

                if (!mainProp->helpText().isEmpty())
                {
                    m_label->setToolTip(mainProp->helpText());
                }
            }
            else
            {
                m_label->setVisible(false);
            }

            if (mainProp->orientation() == Qt::Horizontal)
            {
                m_layout->setDirection(QBoxLayout::LeftToRight);
                m_layout->setStretchFactor(m_label, mainProp->nameStretch());
                m_layout->setStretchFactor(m_widget, mainProp->widgetStretch());
            }
            else
            {
                m_layout->setDirection(QBoxLayout::TopToBottom);
                m_layout->setStretchFactor(m_label, 0);
                m_layout->setStretchFactor(m_widget, 1);
            }
        }

        void InspectorPropertyWidget::showEvent(QShowEvent* event)
        {
            Q_UNUSED(event);
            emit visibilityChanged(true);
        }

        void InspectorPropertyWidget::hideEvent(QHideEvent* event)
        {
            Q_UNUSED(event);
            emit visibilityChanged(false);
        }

        InspectorGroupWidget::InspectorGroupWidget(const QList<InspectorGroup*>& groups, QWidget* parent) :
            QWidget(parent),
            m_groups(groups),
            m_layout(new QVBoxLayout),
            m_expander(new ExpanderWidget),
            m_content(nullptr),
            m_contentLayout(nullptr),
            m_firstRefresh(true)
        {
            InspectorGroup* mainGroup = groups[0];

            qDebug().noquote() << QString("Creating inspector group widget (id: %1)").arg(mainGroup->id());

            m_layout->setContentsMargins(0, 0, 0, 0);
            m_layout->setSizeConstraint(QLayout::SetMinimumSize);
            m_layout->setAlignment(Qt::AlignTop);

            setLayout(m_layout);

            refreshGroup();
        }

        void InspectorGroupWidget::refreshGroup()
        {
            if (m_content)
            {
                delete m_content;
            }

            for (InspectorGroup* group : m_groups)
            {
                group->disconnect(this);
                m_expander->disconnect(group);
            }

            InspectorGroup* mainGroup = m_groups[0];

            m_content = new QWidget;
            m_contentLayout = new QVBoxLayout;

            m_contentLayout->setAlignment(Qt::AlignTop);
            m_content->setLayout(m_contentLayout);

            for (int i = 0; i < mainGroup->itemCount(); i++)
            {
                InspectorGroupItem* item = mainGroup->item(i);

                switch (item->type())
                {
                case InspectorGroupItem::Property:
                {
                    InspectorProperty* firstProp = item->property();
                    QList<InspectorProperty*> similarProps;
                    bool propPresentInAllGroups = true;

                    similarProps.append(firstProp);

                    for (int i = 1; i < m_groups.size(); i++)
                    {
                        if (m_groups[i]->hasProperty(firstProp->name()))
                        {
                            similarProps.append(m_groups[i]->property(firstProp->name()));
                        }
                        else
                        {
                            propPresentInAllGroups = false;
                            break;
                        }
                    }

                    if (propPresentInAllGroups)
                    {
                        QHBoxLayout* propLayout = new QHBoxLayout;

                        propLayout->setContentsMargins(0, 0, 0, 0);

                        InspectorPropertyWidget* propWidget = new InspectorPropertyWidget(similarProps);

                        if (!m_contentLayout->isEmpty())
                        {
                            QFrame* separator = new QFrame;
                            separator->setFrameShape(QFrame::HLine);
                            separator->setFrameShadow(QFrame::Sunken);
                            separator->setVisible(propWidget->isVisible());

                            m_contentLayout->addWidget(separator);

                            connect(propWidget, &InspectorPropertyWidget::visibilityChanged, separator, &QFrame::setVisible);
                        }

                        propLayout->addWidget(propWidget, 1);

                        if (mainGroup->isList())
                        {
                            QToolButton* removeButton = new QToolButton;
                            removeButton->setIcon(QIcon(":/icons/list-remove.svg"));
                            removeButton->setAutoRaise(true);

                            connect(removeButton, &QToolButton::clicked, this, [=]
                            {
                                for (InspectorGroup* group : m_groups)
                                {
                                    group->removeListItem(i);
                                }

                                refreshGroup();
                            }, Qt::QueuedConnection);

                            propLayout->addWidget(removeButton, 0, Qt::AlignTop);
                        }

                        m_contentLayout->addLayout(propLayout);
                    }

                    break;
                }
                case InspectorGroupItem::Group:
                {
                    InspectorGroup* firstGroup = item->group();
                    QList<InspectorGroup*> similarGroups;
                    bool groupPresentInAllGroups = true;

                    similarGroups.append(firstGroup);

                    for (int i = 1; i < m_groups.size(); i++)
                    {
                        bool found = false;

                        for (InspectorGroup* group : m_groups[i]->groups())
                        {
                            if (group->equals(firstGroup))
                            {
                                similarGroups.append(group);
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                        {
                            groupPresentInAllGroups = false;
                            break;
                        }
                    }

                    if (groupPresentInAllGroups)
                    {
                        QHBoxLayout* groupLayout = new QHBoxLayout;

                        groupLayout->setContentsMargins(0, 0, 0, 0);

                        InspectorGroupWidget* groupWidget = new InspectorGroupWidget(similarGroups);

                        groupLayout->addWidget(groupWidget, 1);

                        if (mainGroup->isList())
                        {
                            QToolButton* removeButton = new QToolButton;
                            removeButton->setIcon(QIcon(":/icons/list-remove.svg"));
                            removeButton->setAutoRaise(true);

                            connect(removeButton, &QToolButton::clicked, this, [=]
                            {
                                for (InspectorGroup* group : m_groups)
                                {
                                    group->removeListItem(i);
                                }

                                refreshGroup();
                            }, Qt::QueuedConnection);

                            groupLayout->addWidget(removeButton, 0, Qt::AlignTop);
                        }

                        m_contentLayout->addLayout(groupLayout);
                    }

                    break;
                }
                }
            }

            if (mainGroup->isList())
            {
                QPushButton* addButton = new QPushButton;
                addButton->setIcon(QIcon(":/icons/list-add.svg"));

                connect(addButton, &QToolButton::clicked, this, [=]
                {
                    for (InspectorGroup* group : m_groups)
                    {
                        group->addListItem();
                    }

                    refreshGroup();
                }, Qt::QueuedConnection);

                m_contentLayout->addWidget(addButton);
            }

            m_contentLayout->addStretch(1);

            for (InspectorGroup* group : m_groups)
            {
                connect(group, &InspectorGroup::nameChanged, this, &InspectorGroupWidget::refreshWidget);
                connect(group, &InspectorGroup::displayNameChanged, this, &InspectorGroupWidget::refreshWidget);
                connect(group, &InspectorGroup::visibilityChanged, this, &InspectorGroupWidget::refreshWidget);
                connect(group, &InspectorGroup::nameVisibilityChanged, this, &InspectorGroupWidget::refreshWidget);
                connect(group, &InspectorGroup::expansionChanged, this, &InspectorGroupWidget::refreshWidget);
                connect(group, &InspectorGroup::helpTextChanged, this, &InspectorGroupWidget::refreshWidget);

                connect(m_expander, &ExpanderWidget::toggled, group, &InspectorGroup::setExpanded);
            }

            refreshWidget();
        }

        void InspectorGroupWidget::refreshWidget()
        {
            emit refreshStarted();

            InspectorGroup* mainGroup = m_groups[0];

            if (!m_firstRefresh)
            {
                qDebug().noquote() << QString("Refreshing inspector group widget (id: %1)").arg(mainGroup->id());
            }
            else
            {
                m_firstRefresh = false;
            }

            for (InspectorGroup* group : m_groups)
            {
                if (!group->visible())
                {
                    setVisible(false);
                    return;
                }
            }

            if (parentWidget())
            {
                setVisible(true);
            }

            m_layout->removeWidget(m_expander);
            m_layout->removeWidget(m_content);

            if (mainGroup->nameVisible())
            {
                m_contentLayout->unsetContentsMargins();

                QString displayName = mainGroup->displayName();

                if (displayName.isEmpty())
                {
                    if (mainGroup->parentGroup() && mainGroup->parentGroup()->isList())
                    {
                        displayName = mainGroup->name();
                    }
                    else
                    {
                        qDebug().noquote() << QString("Warning: no display name set for group (id: %1)").arg(mainGroup->id());
                        displayName = makeDisplayName(mainGroup->name());
                    }
                }

                if (mainGroup->isList())
                {
                    displayName += QString(" (%1)").arg(mainGroup->itemCount());
                }

                m_expander->setTitle(displayName);
                m_expander->setWidget(m_content);
                m_expander->setExpanded(mainGroup->expanded());

                if (!mainGroup->helpText().isEmpty())
                {
                    m_expander->setToolTip(mainGroup->helpText());
                }

                m_layout->addWidget(m_expander);
            }
            else
            {
                m_contentLayout->setContentsMargins(0, 0, 0, 0);

                m_layout->addWidget(m_content);
            }

            adjustSize();

            emit refreshFinished();
        }

        QString makeDisplayName(const QString& name)
        {
            if (name.isEmpty())
            {
                return QString();
            }

            QList<QString> words;
            QString word;

            for (int i = 0; i < name.size(); i++)
            {
                QChar c = name[i];

                if (c.isUpper())
                {
                    if (!word.isEmpty())
                    {
                        words.append(word);
                    }

                    word = c;
                }
                else if (!c.isLetterOrNumber())
                {
                    if (!word.isEmpty())
                    {
                        words.append(word);
                    }

                    word = QString();
                    i++;
                }
                else
                {
                    word += c;
                }
            }

            if (!word.isEmpty())
            {
                words.append(word);
            }

            for (int i = 0; i < words.size(); i++)
            {
                words[i][0] = words[i][0].toUpper();
            }

            return words.join(' ');
        }

    }

}
