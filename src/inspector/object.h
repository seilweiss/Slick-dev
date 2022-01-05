#pragma once

#include "inspector/root.h"

#include <QMap>
#include <QWidget>

namespace Slick {

    namespace Inspector {

        struct ObjectGroupState
        {
            bool expanded;
        };

        struct ObjectState
        {
            QMap<QString, ObjectGroupState> groups;
            bool previewExpanded;
        };

        class Object
        {
        public:
            Object()
            {
                m_state.previewExpanded = true;
            }

            ObjectState& objectState() { return m_state; }
            const ObjectState& objectState() const { return m_state; }

            virtual void inspect(Root* root) = 0;
            virtual QWidget* createPreview() { return nullptr; }

        private:
            ObjectState m_state;
        };

    }

}
