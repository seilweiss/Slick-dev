#pragma once

#include <QObject>
#include <QWidget>
#include <QEvent>

namespace Slick {

    namespace Inspector {

        // BUG: QComboBox doesn't seem to receive events on Windows... meaning WheelIgnorer doesn't work with it

        class WheelIgnorer : public QObject
        {
            Q_OBJECT

        public:
            WheelIgnorer(QObject* parent = nullptr) : QObject(parent) {}

        protected:
            bool eventFilter(QObject* obj, QEvent* event)
            {
                QWidget* widget = qobject_cast<QWidget*>(obj);

                if (event->type() == QEvent::Wheel && widget && !widget->hasFocus())
                {
                    event->ignore();
                    return true;
                }

                return QObject::eventFilter(obj, event);
            }
        };

    }

}
