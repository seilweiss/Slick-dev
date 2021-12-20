#include "UI/InspectorPanelPrivate.h"

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
                    displayName = makeDisplayName(mainProp->name());
                }

                m_label->setText(displayName);
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
            m_content(new QWidget),
            m_contentLayout(new QVBoxLayout),
            m_firstRefresh(true)
        {
            InspectorGroup* mainGroup = groups[0];

            qDebug().noquote() << QString("Creating inspector group widget (id: %1)").arg(mainGroup->id());

            m_layout->setContentsMargins(0, 0, 0, 0);
            m_layout->setSizeConstraint(QLayout::SetMinimumSize);
            m_layout->setAlignment(Qt::AlignTop);

            setLayout(m_layout);

            m_contentLayout->setAlignment(Qt::AlignTop);
            m_content->setLayout(m_contentLayout);

            for (InspectorGroupItem* item : mainGroup->items())
            {
                switch (item->type())
                {
                case InspectorGroupItem::Property:
                {
                    InspectorProperty* firstProp = item->property();
                    QList<InspectorProperty*> similarProps;
                    bool propPresentInAllGroups = true;

                    similarProps.append(firstProp);

                    for (int i = 1; i < groups.size(); i++)
                    {
                        if (groups[i]->hasProperty(firstProp->name()))
                        {
                            similarProps.append(groups[i]->property(firstProp->name()));
                        }
                        else
                        {
                            propPresentInAllGroups = false;
                            break;
                        }
                    }

                    if (propPresentInAllGroups)
                    {
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

                        m_contentLayout->addWidget(propWidget);
                    }

                    break;
                }
                case InspectorGroupItem::Group:
                {
                    InspectorGroup* firstGroup = item->group();
                    QList<InspectorGroup*> similarGroups;
                    bool groupPresentInAllGroups = true;

                    similarGroups.append(firstGroup);

                    for (int i = 1; i < groups.size(); i++)
                    {
                        bool found = false;

                        for (InspectorGroup* group : groups[i]->groups())
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
                        InspectorGroupWidget* groupWidget = new InspectorGroupWidget(similarGroups);

                        m_contentLayout->addWidget(groupWidget);
                    }

                    break;
                }
                }
            }

            refresh();

            for (InspectorGroup* group : m_groups)
            {
                connect(group, &InspectorGroup::nameChanged, this, &InspectorGroupWidget::refresh);
                connect(group, &InspectorGroup::displayNameChanged, this, &InspectorGroupWidget::refresh);
                connect(group, &InspectorGroup::visibilityChanged, this, &InspectorGroupWidget::refresh);
                connect(group, &InspectorGroup::nameVisibilityChanged, this, &InspectorGroupWidget::refresh);
                connect(group, &InspectorGroup::expansionChanged, this, &InspectorGroupWidget::refresh);

                connect(m_expander, &ExpanderWidget::toggled, group, &InspectorGroup::setExpanded);
            }
        }

        void InspectorGroupWidget::refresh()
        {
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
                    displayName = makeDisplayName(mainGroup->name());
                }

                qDebug() << displayName;

                m_expander->setTitle(displayName);
                m_expander->setWidget(m_content);
                m_expander->setExpanded(mainGroup->expanded());

                m_layout->addWidget(m_expander);
            }
            else
            {
                m_contentLayout->setContentsMargins(0, 0, 0, 0);

                m_layout->addWidget(m_content);
            }
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
