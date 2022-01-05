#include "panels/inspectorpanel.h"

#include "panels/inspectorpanelprivate.h"
#include "util/expandwidget.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

namespace Slick {

    namespace Panels {

        using namespace InspectorPanelPrivate;

        InspectorPanel::InspectorPanel(QWidget* parent) :
            QWidget(parent),
            m_mainLayout(new QVBoxLayout),
            m_scrollArea(new QScrollArea),
            m_rootGroupWidget(nullptr),
            m_previewContainer(new Util::ExpandWidget(tr("Preview")))
        {
            m_scrollArea->setFrameShape(QFrame::NoFrame);
            m_scrollArea->setStyleSheet("QScrollArea { border: 0; }");
            m_scrollArea->setWidgetResizable(true);
            m_scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

            m_scrollArea->setWidget(new QWidget);

            m_mainLayout->addWidget(m_scrollArea, 1);
            m_mainLayout->addWidget(m_previewContainer);

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

            if (m_previewContainer->widget())
            {
                delete m_previewContainer->widget();
                m_previewContainer->setWidget(nullptr);
            }

            m_previewContainer->hide();

            for (Inspector::Root* root : m_roots)
            {
                delete root;
            }

            m_roots.clear();

            if (!m_objects.empty())
            {
                QList<Inspector::Group*> groups;

                for (Inspector::Object* object : m_objects)
                {
                    Inspector::Root* root = new Inspector::Root(this);

                    object->inspect(root);

                    m_roots.append(root);
                    groups.append(root);

                    connect(root, &Inspector::Root::refreshRequested, this, &InspectorPanel::refresh, Qt::QueuedConnection);
                }

                m_rootGroupWidget = new GroupWidget(groups);

                if (m_objects.size() == 1)
                {
                    updateGroupFromState(groups[0], m_objects[0]->objectState());

                    QWidget* preview = m_objects[0]->createPreview();

                    if (preview)
                    {
                        m_previewContainer->setWidget(preview);
                        m_previewContainer->show();
                    }
                }

                m_scrollArea->setWidget(m_rootGroupWidget);
            }

            m_scrollArea->horizontalScrollBar()->setValue(oldHScroll);
            m_scrollArea->verticalScrollBar()->setValue(oldVScroll);
        }

        void InspectorPanel::updateGroupFromState(Inspector::Group* group, Inspector::ObjectState& state)
        {
            for (Inspector::GroupItem* item : group->items())
            {
                if (item->isGroup())
                {
                    Inspector::Group* childGroup = item->group();
                    QString id = item->id();

                    if (state.groups.contains(id))
                    {
                        childGroup->setExpanded(state.groups[id].expanded);
                    }
                    else
                    {
                        state.groups[id].expanded = childGroup->expanded();
                    }

                    connect(childGroup, &Inspector::Group::expansionChanged, this, [=](bool expanded)
                    {
                        m_objects[0]->objectState().groups[id].expanded = expanded;
                    });

                    updateGroupFromState(childGroup, state);
                }
            }
        }

        void InspectorPanel::addObject(Inspector::Object* object, bool _refresh)
        {
            m_objects.append(object);

            if (_refresh)
            {
                refresh();
            }
        }

        void InspectorPanel::removeObject(Inspector::Object* object, bool _refresh)
        {
            m_objects.removeOne(object);

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

            m_objects.clear();

            for (Inspector::Root* root : m_roots)
            {
                delete root;
            }

            m_roots.clear();
        }

    }

}
