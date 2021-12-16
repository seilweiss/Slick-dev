#include "InspectorProperties/InspectorPropertyImpl.h"

#include "InspectorProperties/Int8InspectorProperty.h"
#include "InspectorProperties/Int16InspectorProperty.h"
#include "InspectorProperties/Int32InspectorProperty.h"
#include "InspectorProperties/UInt8InspectorProperty.h"
#include "InspectorProperties/UInt16InspectorProperty.h"
#include "InspectorProperties/UInt32InspectorProperty.h"
#include "InspectorProperties/FloatInspectorProperty.h"
#include "InspectorProperties/DoubleInspectorProperty.h"
#include "InspectorProperties/QStringInspectorProperty.h"
#include "InspectorProperties/StdStringInspectorProperty.h"
#include "InspectorProperties/Color8InspectorProperty.h"

#include "Core/Util.h"

#include <QLineEdit>
#include <QPlainTextEdit>

#include <limits>

namespace Slick {

    namespace {

        template <class Prop, class Num, class SpinBox>
        QWidget* createSpinBox(const QVector<InspectorProperty*>& props)
        {
            SpinBox* spinBox = new SpinBox;
            Num value = ((Prop*)props[0])->data();
            bool match = true;

            for (int i = 1; i < props.size(); i++)
            {
                Num data = ((Prop*)props[i])->data();

                if (data != value)
                {
                    match = false;
                    break;
                }
            }

            spinBox->setEmpty(!match);
            spinBox->setRange(std::numeric_limits<Num>::min(), std::numeric_limits<Num>::max());
            spinBox->setValue(value);

            QObject::connect(spinBox, &SpinBox::valueChanged, [=](Num value)
            {
                for (InspectorProperty* prop : props)
                {
                    ((Prop*)prop)->setData(value);
                    prop->notifyDataChanged();
                }
            });

            return spinBox;
        }

        template <class Prop, class Str>
        QWidget* createStringWidget(const QVector<InspectorProperty*>& props)
        {
            QWidget* widget;
            Prop* prop = (Prop*)props[0];
            Str text = prop->data();
            bool match = true;

            for (int i = 1; i < props.size(); i++)
            {
                Str data = ((Prop*)props[i])->data();

                if (data != text)
                {
                    match = false;
                    break;
                }
            }

            QString editText = match ? Util::convertString<QString>(text) : QString();

            if (prop->multiline())
            {
                QPlainTextEdit* textEdit = new QPlainTextEdit;
                textEdit->setPlainText(editText);
                textEdit->setFont(QFontDatabase::systemFont(prop->monospace() ? QFontDatabase::FixedFont : QFontDatabase::GeneralFont));

                QObject::connect(textEdit, &QPlainTextEdit::textChanged, [=]
                {
                    for (InspectorProperty* prop : props)
                    {
                        ((Prop*)prop)->setData(Util::convertString<Str>(textEdit->toPlainText()));
                        prop->notifyDataChanged();
                    }
                });

                widget = textEdit;
            }
            else
            {
                QLineEdit* lineEdit = new QLineEdit;
                lineEdit->setText(editText);
                lineEdit->setFont(QFontDatabase::systemFont(prop->monospace() ? QFontDatabase::FixedFont : QFontDatabase::GeneralFont));

                QObject::connect(lineEdit, &QLineEdit::textEdited, [=](const QString& text)
                {
                    for (InspectorProperty* prop : props)
                    {
                        ((Prop*)prop)->setData(Util::convertString<Str>(text));
                        prop->notifyDataChanged();
                    }
                });

                widget = lineEdit;
            }

            return widget;
        }

        template <class Prop, class Num, bool alpha>
        QWidget* createColorWidget(const QVector<InspectorProperty*>& props)
        {
            QFrame* frame = new QFrame;
            QPalette palette;
            Num* color = ((Prop*)props[0])->data();
            bool match = true;

            for (int i = 1; i < props.size(); i++)
            {
                Num* data = ((Prop*)props[i])->data();

                if (memcmp(data, color, sizeof(Num) * (alpha ? 4 : 3)) != 0)
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                palette.setColor(QPalette::Window, QColor(color[0], color[1], color[2], (alpha ? color[3] : 255)));
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

    QWidget* Int8InspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<Int8InspectorProperty, int8_t, IntSpinBox>(props);
    }

    QWidget* Int16InspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<Int16InspectorProperty, int16_t, IntSpinBox>(props);
    }

    QWidget* Int32InspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<Int32InspectorProperty, int32_t, IntSpinBox>(props);
    }

    QWidget* UInt8InspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<UInt8InspectorProperty, uint8_t, IntSpinBox>(props);
    }

    QWidget* UInt16InspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<UInt16InspectorProperty, uint16_t, IntSpinBox>(props);
    }

    QWidget* UInt32InspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<UInt32InspectorProperty, uint32_t, IntSpinBox>(props);
    }

    QWidget* FloatInspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<FloatInspectorProperty, float, DoubleSpinBox>(props);
    }

    QWidget* DoubleInspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createSpinBox<DoubleInspectorProperty, double, DoubleSpinBox>(props);
    }

    QWidget* QStringInspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createStringWidget<QStringInspectorProperty, QString>(props);
    }

    QWidget* StdStringInspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createStringWidget<StdStringInspectorProperty, std::string>(props);
    }

    QWidget* Color8InspectorProperty::createWidget(const QVector<InspectorProperty*>& props)
    {
        return createColorWidget<Color8InspectorProperty, uint8_t, true>(props);
    }

}
