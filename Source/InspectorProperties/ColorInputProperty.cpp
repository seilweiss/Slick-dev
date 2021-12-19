#include "InspectorProperties/ColorInputProperty.h"

#include <QFrame>

namespace Slick {

    namespace {

        template <class T> QWidget* createColorInput(const QList<InspectorProperty*>& props)
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

    QWidget* ColorInputProperty::createWidget(const QList<InspectorProperty*>& props)
    {
        switch (props[0]->dataSource().type())
        {
        case InspectorDataSource::Color: return createColorInput<Color>(props);
        case InspectorDataSource::ColorF: return createColorInput<ColorF>(props);
        default: return createColorInput<ColorF>(props);
        }
    }

}
