#pragma once

#include "Core/Inspector.h"

#include <QWidget>

class QVBoxLayout;

namespace Slick {

    class InspectorPanel : public QWidget
    {
        Q_OBJECT

    public:
        static InspectorPanel* instance()
        {
            static InspectorPanel* theInstance = new InspectorPanel;
            return theInstance;
        }

        void refresh();

        void addInspector(Inspector* inspector, bool refresh = true);
        void removeInspector(Inspector* inspector, bool refresh = true);
        void clear(bool refresh = true);
        Inspector* inspector(int index) const { return m_inspectors[index]; }
        int count() const { return m_inspectors.size(); }

    private:
        InspectorPanel(QWidget* parent = nullptr);

        QVector<Inspector*> m_inspectors;
        QVBoxLayout* m_mainLayout;
        QWidget* m_inspectorWidget;
        QVBoxLayout* m_inspectorLayout;

        void recurseAddGroups(QVBoxLayout* parentLayout, const QVector<InspectorGroup*>& groups, bool root);
    };

}
