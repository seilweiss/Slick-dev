#pragma once

#include "inspector/properties/wheelignorer.h"

#include <QSpinBox>

namespace Slick {

    namespace Inspector {

        // BUG: Right border not drawn correctly with NoButtons

        class IntSpinBox : public QSpinBox
        {
            Q_OBJECT
            Q_PROPERTY(bool empty READ empty WRITE setEmpty)

        public:
            IntSpinBox(QWidget* parent = nullptr) : QSpinBox(parent)
            {
                setFocusPolicy(Qt::StrongFocus);
                installEventFilter(new WheelIgnorer(this));
            }

            bool empty() const { return m_empty; }
            void setEmpty(bool empty) { m_empty = empty; }

            virtual QSize sizeHint() const override { return QSize(32, QSpinBox::sizeHint().height()); }
            virtual QSize minimumSizeHint() const override { return QSize(32, QSpinBox::minimumSizeHint().height()); }

        protected:
            virtual QString textFromValue(int value) const override { return m_empty ? QString() : QString::number(value); }
            //virtual void resizeEvent(QResizeEvent* event) override { setButtonSymbols(event->size().width() < 64 ? QAbstractSpinBox::NoButtons : QAbstractSpinBox::UpDownArrows); }

        private:
            bool m_empty;
        };

    }

}
