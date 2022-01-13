#include "inspector/properties/labelproperty.h"

#include "util/stringutils.h"

#include <QLabel>

namespace Slick {

    namespace Inspector {

        namespace {

            QWidget* createLabel()
            {
                QLabel* label = new QLabel;

                return label;
            }

            template <class T> void updateLabel(QWidget* widget, const QList<Property*>& props)
            {
                QLabel* label = (QLabel*)widget;
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
            }

        }

        QWidget* LabelProperty::createWidget(const QList<Property*>&)
        {
            return createLabel();
        }

        void LabelProperty::updateWidget(QWidget* widget, const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::StdString: updateLabel<std::string>(widget, props); break;
            default: updateLabel<QString>(widget, props); break;
            }
        }

    }

}
