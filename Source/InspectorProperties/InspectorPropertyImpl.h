#pragma once

#include <QSpinBox>
#include <QDoubleSpinBox>

namespace Slick {

    class IntSpinBox : public QSpinBox
    {
        Q_OBJECT
        Q_PROPERTY(bool empty READ empty WRITE setEmpty)

    public:
        IntSpinBox(QWidget* parent = nullptr) : QSpinBox(parent) {}

        bool empty() const { return m_empty; }
        void setEmpty(bool empty) { m_empty = empty; }

    protected:
        virtual QString textFromValue(int value) const override { return m_empty ? QString() : QString::number(value); }

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

    protected:
        virtual QString textFromValue(double value) const override { return m_empty ? QString() : QString::number(value); }

    private:
        bool m_empty;
    };

}
