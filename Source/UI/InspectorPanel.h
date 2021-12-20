#pragma once

#include "Core/Inspectable.h"

#include <QWidget>

class QVBoxLayout;
class QScrollArea;

namespace Slick {

    namespace InspectorPanelPrivate {

        class InspectorGroupWidget;

    }

    class InspectorPanel : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(int count READ count)

    public:
        static InspectorPanel* instance()
        {
            static InspectorPanel* theInstance = new InspectorPanel;
            return theInstance;
        }

        void refresh();

        void addInspectable(Inspectable* inspectable, bool refresh = true);
        void removeInspectable(Inspectable* inspectable, bool refresh = true);
        void clear();
        Inspectable* inspectable(int index) const { return m_inspectables[index]; }
        int count() const { return m_inspectables.size(); }

    private:
        InspectorPanel(QWidget* parent = nullptr);

        QList<Inspectable*> m_inspectables;
        QList<Inspector*> m_inspectors;
        QVBoxLayout* m_mainLayout;
        QScrollArea* m_scrollArea;
        InspectorPanelPrivate::InspectorGroupWidget* m_rootGroupWidget;

        void updateGroupFromState(InspectorGroup* group, InspectorState& state);
    };

}
