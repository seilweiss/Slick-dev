#pragma once

#include "Core/InspectorGroup.h"

namespace Slick {

    class Inspector : public InspectorGroup
    {
        Q_OBJECT

    public:
        Inspector(QObject* parent = nullptr);
    };

}
