#include "inspector/properties/colorinputproperty.h"

#include <QFrame>

namespace Slick {

    namespace Inspector {

        namespace {

            template <class T> QWidget* createColorInput(const QList<Property*>& props)
            {
                QFrame* frame = new QFrame;
                QPalette palette;
                T color = props[0]->dataSource().data<T>();
                bool match = true;

                for (int i = 1; i < props.size(); i++)
                {
                    T data = props[i]->dataSource().data<T>();

                    if (data != color)
                    {
                        match = false;
                        break;
                    }
                }

                if (match)
                {
                    palette.setColor(QPalette::Window, color.toQColor());
                }
                else
                {
                    palette.setBrush(QPalette::Window, QBrush(QColor(255, 0, 0), Qt::BDiagPattern));
                }

                frame->setAutoFillBackground(true);
                frame->setPalette(palette);
                frame->setFrameShape(QFrame::StyledPanel);

                return frame;
            }

        }

        QWidget* ColorInputProperty::createWidget(const QList<Property*>& props)
        {
            switch (props[0]->dataSource().type())
            {
            case DataSource::Color: return createColorInput<Core::Color>(props);
            case DataSource::ColorF: return createColorInput<Core::ColorF>(props);
            default: return createColorInput<Core::ColorF>(props);
            }
        }

    }

}
