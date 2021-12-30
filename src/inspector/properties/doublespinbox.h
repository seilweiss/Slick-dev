#pragma once

#include "inspector/properties/wheelignorer.h"

#include <QDoubleSpinBox>

namespace Slick {

    namespace Inspector {

        // BUG: Right border not drawn correctly with NoButtons

        class DoubleSpinBox : public QDoubleSpinBox
        {
            Q_OBJECT
            Q_PROPERTY(bool empty READ empty WRITE setEmpty)

        public:
            DoubleSpinBox(QWidget* parent = nullptr) : QDoubleSpinBox(parent)
            {
                setFocusPolicy(Qt::StrongFocus);
                installEventFilter(new WheelIgnorer(this));
            }

            bool empty() const { return m_empty; }
            void setEmpty(bool empty) { m_empty = empty; }

            virtual QSize sizeHint() const override { return QSize(32, QDoubleSpinBox::sizeHint().height()); }
            virtual QSize minimumSizeHint() const override { return QSize(32, QDoubleSpinBox::minimumSizeHint().height()); }

        protected:
            virtual QString textFromValue(double value) const override { return m_empty ? QString() : QString::number(value); }
            //virtual void resizeEvent(QResizeEvent* event) override { setButtonSymbols(event->size().width() < 64 ? QAbstractSpinBox::NoButtons : QAbstractSpinBox::UpDownArrows); }

        private:
            bool m_empty;
        };

    }

}
