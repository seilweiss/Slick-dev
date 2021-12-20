#include "UI/InspectorPanel.h"

#include "UI/InspectorPanelPrivate.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
//#include <QHBoxLayout>
//#include <QLabel>

namespace Slick {

    using namespace InspectorPanelPrivate;

    InspectorPanel::InspectorPanel(QWidget* parent) :
        QWidget(parent),
        m_mainLayout(new QVBoxLayout),
        m_scrollArea(new QScrollArea),
        m_rootGroupWidget(nullptr)
    {
        m_scrollArea->setFrameShape(QFrame::NoFrame);
        m_scrollArea->setStyleSheet("QScrollArea { border: 0; }");
        m_scrollArea->setWidgetResizable(true);
        m_scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        m_scrollArea->setWidget(new QWidget);

        m_mainLayout->addWidget(m_scrollArea, 1);

        setLayout(m_mainLayout);
        refresh();
    }

    void InspectorPanel::refresh()
    {
        qDebug("Inspector refresh");

        int oldHScroll = m_scrollArea->horizontalScrollBar()->value();
        int oldVScroll = m_scrollArea->verticalScrollBar()->value();

        if (m_rootGroupWidget)
        {
            delete m_rootGroupWidget;
            m_rootGroupWidget = nullptr;
        }

        for (Inspector* inspector : m_inspectors)
        {
            delete inspector;
        }

        m_inspectors.clear();

        if (!m_inspectables.empty())
        {
            QList<InspectorGroup*> groups;

            for (Inspectable* inspectable : m_inspectables)
            {
                Inspector* inspector = new Inspector(this);

                inspectable->inspect(inspector);

                m_inspectors.append(inspector);
                groups.append(inspector);

                connect(inspector, &Inspector::refreshRequested, this, &InspectorPanel::refresh, Qt::QueuedConnection);
            }

            m_rootGroupWidget = new InspectorGroupWidget(groups);

            if (m_inspectables.size() == 1)
            {
                updateGroupFromState(groups[0], m_inspectables[0]->inspectorState());
            }

            m_scrollArea->setWidget(m_rootGroupWidget);
        }

        m_scrollArea->horizontalScrollBar()->setValue(oldHScroll);
        m_scrollArea->verticalScrollBar()->setValue(oldVScroll);
    }

    void InspectorPanel::updateGroupFromState(InspectorGroup* group, InspectorState& state)
    {
        for (InspectorGroupItem* item : group->items())
        {
            if (item->isGroup())
            {
                InspectorGroup* childGroup = item->group();
                QString id = item->id();

                if (state.groups.contains(id))
                {
                    childGroup->setExpanded(state.groups[id].expanded);
                }
                else
                {
                    state.groups[id].expanded = childGroup->expanded();
                }

                connect(childGroup, &InspectorGroup::expansionChanged, this, [=](bool expanded)
                {
                    m_inspectables[0]->inspectorState().groups[id].expanded = expanded;
                });

                updateGroupFromState(childGroup, state);
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
        if (m_rootGroupWidget)
        {
            delete m_rootGroupWidget;
            m_rootGroupWidget = nullptr;
        }

        m_inspectables.clear();

        for (Inspector* inspector : m_inspectors)
        {
            delete inspector;
        }

        m_inspectors.clear();
    }

}
