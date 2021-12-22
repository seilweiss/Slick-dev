#include "Core/Inspector.h"

namespace Slick {

    Inspector::Inspector(QObject* parent) :
        InspectorGroup("root", QString(), parent)
    {
        setNameVisible(false);
    }

}
