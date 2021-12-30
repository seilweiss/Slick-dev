#include "inspector/root.h"

namespace Slick {

    namespace Inspector {

        Root::Root(QObject* parent) :
            Group("root", QString(), parent)
        {
            setNameVisible(false);
        }

    }

}
