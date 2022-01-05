#include "inspector/properties/labelproperty.h"

#include "util/stringutils.h"

#include <QLabel>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class T> QWidget* createLabel(const QList<Property*>& props)
            {
                QLabel* label = new QLabel;
                T text = props[0]->dataSource().data<T>();
                bool match = true;

                for (int i = 1; i < props.size(); i++)
                {
                    T data = props[i]->dataSource().data<T>();

                    if (data != text)
                    {
                        match = false;
                        break;
                    }
                }

                label->setText(match ? Util::convertString<QString>(text) : QString());

                return label;
            }

        }

        QWidget* LabelProperty::createWidget(const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::StdString: return createLabel<std::string>(props);
            default: return createLabel<QString>(props);
            }
        }

    }

}
