#pragma once

#include <QLayout>
#include <QWidget>

namespace Slick {

    namespace Util {

        inline void clearLayout(QLayout* layout)
        {
            if (!layout)
            {
                return;
            }

            while (QLayoutItem* item = layout->takeAt(0))
            {
                if (item->layout())
                {
                    clearLayout(item->layout());
                    delete item->layout();
                }
                else if (item->widget())
                {
                    delete item->widget();
                }

                //layout->removeItem(item);
                //delete item;
            }
        }

    }

}
