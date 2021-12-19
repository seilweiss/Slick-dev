#pragma once

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QResizeEvent>

namespace Slick {

    // BUG: Right border of IntSpinBox and DoubleSpinBox not drawn correctly with NoButtons

    class IntSpinBox : public QSpinBox
    {
        Q_OBJECT
        Q_PROPERTY(bool empty READ empty WRITE setEmpty)

    public:
        IntSpinBox(QWidget* parent = nullptr) : QSpinBox(parent) {}

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

    class DoubleSpinBox : public QDoubleSpinBox
    {
        Q_OBJECT
        Q_PROPERTY(bool empty READ empty WRITE setEmpty)

    public:
        DoubleSpinBox(QWidget* parent = nullptr) : QDoubleSpinBox(parent) {}

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
