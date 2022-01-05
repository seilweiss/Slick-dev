#pragma once

#include "inspector/object.h"

#include <QWidget>

class QVBoxLayout;
class QScrollArea;

namespace Slick {

    namespace Util { class ExpandWidget; }

    namespace Panels {

        namespace InspectorPanelPrivate { class GroupWidget; }

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

            void addObject(Inspector::Object* object, bool refresh = true);
            void removeObject(Inspector::Object* object, bool refresh = true);
            void clear();
            Inspector::Object* object(int index) const { return m_objects[index]; }
            int count() const { return m_objects.size(); }

        private:
            InspectorPanel(QWidget* parent = nullptr);

            QList<Inspector::Object*> m_objects;
            QList<Inspector::Root*> m_roots;
            QVBoxLayout* m_mainLayout;
            QScrollArea* m_scrollArea;
            InspectorPanelPrivate::GroupWidget* m_rootGroupWidget;
            Util::ExpandWidget* m_previewContainer;

            void updateGroupFromState(Inspector::Group* group, Inspector::ObjectState& state);
        };

    }

}
