#include "UI/InspectorPanel.h"

#include "UI/ExpanderWidget.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

namespace Slick {

    namespace {

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

    InspectorPanel::InspectorPanel(QWidget* parent) :
        QWidget(parent),
        m_mainLayout(new QVBoxLayout),
        m_scrollArea(new QScrollArea),
        m_inspectorWidget(nullptr),
        m_inspectorLayout(nullptr)
    {
        m_scrollArea->setFrameShape(QFrame::NoFrame);
        m_scrollArea->setStyleSheet("QScrollArea { border: 0; }");
        m_scrollArea->setWidgetResizable(true);
        m_scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        m_mainLayout->addWidget(m_scrollArea, 1);

        setLayout(m_mainLayout);
        refresh();
    }

    void InspectorPanel::refresh()
    {
        qDebug("Inspector refresh");

        clearWidget();

        m_groupWidgets.clear();
        m_currentGroupId = QString();

        m_inspectorWidget = new QScrollArea;
        m_inspectorLayout = new QVBoxLayout;

        m_inspectorLayout->setContentsMargins(0, 0, 0, 0);
        m_inspectorLayout->setAlignment(Qt::AlignTop);
        m_inspectorLayout->setSizeConstraint(QLayout::SetMinimumSize);

        m_inspectorWidget->setLayout(m_inspectorLayout);

        if (!m_inspectables.empty())
        {
            QList<InspectorGroup*> groups;

            for (Inspectable* inspectable : m_inspectables)
            {
                Inspector* inspector = new Inspector(this);

                inspectable->inspect(inspector);

                m_inspectors.append(inspector);
                groups.append(inspector);
            }

            recurseAddGroups(m_inspectorLayout, groups, true);

            if (m_inspectables.size() == 1)
            {
                InspectorState& state = m_inspectables[0]->inspectorState();

                for (const QString& id : m_groupWidgets.keys())
                {
                    if (state.groups.contains(id))
                    {
                        m_groupWidgets[id]->setExpanded(state.groups[id].expanded);
                    }
                    else
                    {
                        state.groups[id].expanded = m_groupWidgets[id]->isExpanded();
                    }

                    connect(m_groupWidgets[id], &ExpanderWidget::toggled, this, [=](bool expanded)
                    {
                        m_inspectables[0]->inspectorState().groups[id].expanded = expanded;
                    });
                }
            }
        }

        m_inspectorLayout->addStretch(1);

        m_scrollArea->setWidget(m_inspectorWidget);
    }

    void InspectorPanel::recurseAddGroups(QVBoxLayout* parentLayout, const QList<InspectorGroup*>& groups, bool root)
    {
        InspectorGroup* mainGroup = groups[0];
        QVBoxLayout* groupLayout = parentLayout;

        if (!m_currentGroupId.isEmpty())
        {
            m_currentGroupId += ".";
        }

        m_currentGroupId += mainGroup->name();

        if (!root && mainGroup->nameVisible())
        {
            QString displayName = mainGroup->displayName();

            if (displayName.isEmpty())
            {
                displayName = makeDisplayName(mainGroup->name());
            }

            ExpanderWidget* groupWidget = new ExpanderWidget(displayName);
            QWidget* contentWidget = new QWidget;

            groupLayout = new QVBoxLayout;
            groupLayout->setAlignment(Qt::AlignTop);

            contentWidget->setLayout(groupLayout);

            groupWidget->setWidget(contentWidget);
            groupWidget->setExpanded(mainGroup->expanded());

            parentLayout->addWidget(groupWidget);

            m_groupWidgets[m_currentGroupId] = groupWidget;
        }

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
                    QWidget* propWidget = firstProp->createWidget(similarProps);

                    if (propWidget)
                    {
                        QLabel* propLabel = nullptr;

                        if (firstProp->nameVisible())
                        {
                            QString displayName = firstProp->displayName();

                            if (displayName.isEmpty())
                            {
                                displayName = makeDisplayName(firstProp->name());
                            }

                            propLabel = new QLabel(displayName);
                        }

                        QBoxLayout* propLayout;

                        if (firstProp->orientation() == Qt::Horizontal)
                        {
                            propLayout = new QHBoxLayout;

                            if (propLabel)
                            {
                                propLayout->addWidget(propLabel, firstProp->nameStretch());
                            }

                            propLayout->addWidget(propWidget, firstProp->widgetStretch());
                        }
                        else
                        {
                            propLayout = new QVBoxLayout;

                            if (propLabel)
                            {
                                propLayout->addWidget(propLabel, 0);
                            }

                            propLayout->addWidget(propWidget, 1);
                        }

                        if (!groupLayout->isEmpty())
                        {
                            QFrame* separator = new QFrame;
                            separator->setFrameShape(QFrame::HLine);
                            separator->setFrameShadow(QFrame::Sunken);

                            groupLayout->addWidget(separator);
                        }

                        groupLayout->addLayout(propLayout);
                    }
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
                    recurseAddGroups(groupLayout, similarGroups, false);
                }

                break;
            }
            }
        }
    }

    void InspectorPanel::addInspectable(Inspectable* inspectable, bool _refresh)
    {
        m_inspectables.append(inspectable);

        if (_refresh)
        {
            refresh();
        }
    }

    void InspectorPanel::removeInspectable(Inspectable* inspectable, bool _refresh)
    {
        m_inspectables.removeOne(inspectable);

        if (_refresh)
        {
            refresh();
        }
    }

    void InspectorPanel::clear()
    {
        m_inspectables.clear();
        clearWidget();
    }

    void InspectorPanel::clearWidget()
    {
        for (Inspector* inspector : m_inspectors)
        {
            delete inspector;
        }

        m_inspectors.clear();

        if (m_inspectorWidget)
        {
            delete m_inspectorWidget;
            m_inspectorWidget = nullptr;
        }
    }

}
