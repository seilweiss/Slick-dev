#pragma once

#include "inspector/group.h"

namespace Slick {

    namespace Inspector {

        class Root : public Group
        {
            Q_OBJECT

        public:
            Root(QObject* parent = nullptr);
        };

    }

}
