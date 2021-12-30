#pragma once

#include "inspector/root.h"

#include <QMap>

namespace Slick {

    namespace Inspector {

        struct ObjectGroupState
        {
            bool expanded;
        };

        struct ObjectState
        {
            QMap<QString, ObjectGroupState> groups;
        };

        class Object
        {
        public:
            ObjectState& objectState() { return m_state; }
            const ObjectState& objectState() const { return m_state; }

            virtual void inspect(Root* root) = 0;

        private:
            ObjectState m_state;
        };

    }

}
