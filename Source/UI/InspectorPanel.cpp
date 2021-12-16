#include "UI/InspectorPanel.h"

#include "UI/ExpanderWidget.h"

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

            QVector<QString> words;
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
        m_inspectorWidget(nullptr),
        m_inspectorLayout(nullptr)
    {
        setLayout(m_mainLayout);
        refresh();
    }

    void InspectorPanel::refresh()
    {
        qDebug("Inspector refresh");

        if (m_inspectorWidget)
        {
            delete m_inspectorWidget;
        }

        m_inspectorWidget = new QWidget;
        m_inspectorLayout = new QVBoxLayout;

        m_inspectorLayout->setContentsMargins(0, 0, 0, 0);
        m_inspectorLayout->setAlignment(Qt::AlignTop);

        m_inspectorWidget->setLayout(m_inspectorLayout);

        m_mainLayout->addWidget(m_inspectorWidget, 1);

        if (!m_inspectors.empty())
        {
            QVector<InspectorGroup*> groups;

            for (Inspector* inspector : m_inspectors)
            {
                groups.append(inspector);
            }

            recurseAddGroups(m_inspectorLayout, groups, true);
        }

        m_inspectorLayout->addStretch(1);
    }

    void InspectorPanel::recurseAddGroups(QVBoxLayout* parentLayout, const QVector<InspectorGroup*>& groups, bool root)
    {
        InspectorGroup* mainGroup = groups[0];
        QVBoxLayout* groupLayout = parentLayout;

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
            groupWidget->expand();

            parentLayout->addWidget(groupWidget);
        }

        for (InspectorGroupItem* item : mainGroup->items())
        {
            if (item->isProperty())
            {
                InspectorProperty* firstProp = item->property();
                QVector<InspectorProperty*> similarProps;
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
                                propLayout->addWidget(propLabel, 1);
                            }

                            propLayout->addWidget(propWidget, 1);
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

                        groupLayout->addLayout(propLayout);
                    }
                }
            }
            else
            {
                InspectorGroup* firstGroup = item->group();
                QVector<InspectorGroup*> similarGroups;
                bool groupPresentInAllGroups = true;

                similarGroups.append(firstGroup);

                for (int i = 1; i < groups.size(); i++)
                {
                    if (groups[i]->hasGroup(firstGroup->name()))
                    {
                        similarGroups.append(groups[i]->group(firstGroup->name()));
                    }
                    else
                    {
                        groupPresentInAllGroups = false;
                        break;
                    }
                }

                if (groupPresentInAllGroups)
                {
                    recurseAddGroups(groupLayout, similarGroups, false);
                }
            }
        }
    }

    void InspectorPanel::addInspector(Inspector* inspector, bool _refresh)
    {
        m_inspectors.append(inspector);

        if (_refresh)
        {
            refresh();
        }
    }

    void InspectorPanel::removeInspector(Inspector* inspector, bool _refresh)
    {
        m_inspectors.removeOne(inspector);

        if (_refresh)
        {
            refresh();
        }
    }

    void InspectorPanel::clear(bool _refresh)
    {
        m_inspectors.clear();

        if (_refresh)
        {
            refresh();
        }
    }

}
