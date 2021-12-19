#pragma once

#include <QMap>

namespace Slick {

    struct InspectorGroupState
    {
        bool expanded;
    };

    struct InspectorState
    {
        QMap<QString, InspectorGroupState> groups;
    };

}
